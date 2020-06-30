/*******************************************************************************************
**
** Project: Luna Editor
** File: SourceParser.cpp
**
** Copyright (C) 2014 techvoid.
** All rights reserved.
** http://sourceforge.net/projects/lunaeditor/
**
** This program is free software: you can redistribute it and/or modify it under the terms
** of the GNU General Public License as published by the Free Software Foundation, either
** version 3 of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
** without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along with this
** program. If not, see <http://www.gnu.org/licenses/>.
**
*******************************************************************************************/

/*======================================== HEADERS =======================================*/

#include "SourceParser.h"

#include <QtGui/QApplication>
#include <QtGui/QProgressDialog>
#include <QtCore/QRegExp>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QDebug>

#include "CodeEdit.h"
#include "XmlReader.h"

/*======================================== PUBLIC ========================================*/

SourceParser::SourceParser(QWidget *pParent) :
    QObject(pParent),
    rParentWidget(pParent)
{
}

SourceParser::SourceParser(QWidget *pParent, XmlReader *pReader) :
    QObject(pParent),
    rParentWidget(pParent),
    rXmlReader(pReader)
{
}

void SourceParser::ParseDir(QString pDir)
{
    mFileList.clear();
    mDirList.clear();

    QString tDir = pDir;
    if (tDir.isEmpty())
        tDir = QApplication::applicationDirPath();

    QProgressDialog tProgress(rParentWidget);
    tProgress.setCancelButtonText("Abort");
    tProgress.setMinimumSize(tProgress.size());
    tProgress.setMaximumSize(tProgress.size());
    tProgress.setWindowFlags(rParentWidget->windowFlags());
    tProgress.setWindowModality(Qt::WindowModal);
    tProgress.setMinimumDuration(0);
    tProgress.show();

    // search dirs
    tProgress.setLabelText("Calculating...");
    IndexDir(tDir);
    for (int i = 0; i < mDirList.count(); i++) {
        tProgress.setValue(i * -1);

        if (tProgress.wasCanceled())
            return;

        IndexDir(mDirList.at(i)->path());
    }

    int tCount = mFileList.count();
    tProgress.setMaximum(tCount);

    // search lua
    tProgress.setLabelText("Parsing...");
    for (int i = 0; i < tCount; i++) {
        tProgress.setValue(i);

        if (tProgress.wasCanceled())
            break;

        ParseFile(mFileList.at(i)->fileName());
    }

    // save to file & reload
    SaveXml();
    tProgress.setValue(tCount);
}

void SourceParser::ParseFile(QString pFileName)
{
    /** Example of lua hooking:
      * / * Some hints * /
      * lua_register(pLuaState, "PJB_SetImage", &Hook_PJB_SetImage);
      */

    if (pFileName.isEmpty())
        return;

    QFile tFile(pFileName);
    if (!tFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString tText = tFile.readAll();

    //-- Find lua_register function
    QRegExp tLuaRegExp("lua_register\\(.*\\);");
    tLuaRegExp.setMinimal(true);

    QList<Function> tFuncList;

    int tPos = 0, tOldPos = 0;
    while ((tPos = tLuaRegExp.indexIn(tText, tPos)) != -1) {
        Function tFunc;
        tFunc.Name = tLuaRegExp.cap(0);

        //-- Find top comment of lua_register
        QRegExp tLuaComExp("/\\*.*\\*/(?=\\s+" + QRegExp::escape(tFunc.Name) + ")");
        tLuaComExp.setMinimal(true);

        //-- Check if current comment is bellow old lua_register
        if (tLuaComExp.lastIndexIn(tText, tPos) > tOldPos) {
            tFunc.Hint = tLuaComExp.cap(0);
        } else {
            tFunc.Hint = QString("");
        }

        tOldPos = tPos;
        tPos += tLuaRegExp.matchedLength();

        tFuncList << tFunc;
    }

    foreach(Function rFunc, tFuncList) {

        //-- Find first quotation in lua_register, this
        //   should be the name of lua function.
        //   NOTE: It ends at last quotation mark.
        QRegExp tLuaFuncExp("(?:\")(.*)(?=\")");
        tLuaFuncExp.indexIn(rFunc.Name);
        rFunc.Name = tLuaFuncExp.cap(1);
        rFunc.Hint = rFunc.Hint.remove(QRegExp("/\\*\\s+"))   // start
                     .remove(QRegExp("\\s+\\*/"));  // end

        //-- Find and remove spaces between new lines
        tPos = 0;
        QRegExp tHintLineExp("(?:[\\n\\r])([ \\t]+)");
        while ((tPos = tHintLineExp.indexIn(rFunc.Hint, tPos)) != -1) {
            rFunc.Hint.remove(tHintLineExp.cap(1));
            tPos += tHintLineExp.matchedLength();
        }

        qDebug() << rFunc.Name;
        qDebug() << rFunc.Hint;

        if (rXmlReader)
            rXmlReader->AppendCode(rFunc.Name, rFunc.Hint);
    }
}

void SourceParser::SetEditorList(QList<CodeEdit *> pList)
{
    rEditorList = pList;
}

void SourceParser::SaveXml()
{
    if (rXmlReader && rXmlReader->ResaveFile()) {
        foreach(CodeEdit *rEdit, rEditorList) {
            rEdit->SetModelFromReader(rXmlReader);
        }
    }
}

void SourceParser::CleanXml()
{
    if (rXmlReader) {
        rXmlReader->ClearCode();
        SaveXml();
    }
}

/*===================================== PUBLIC SLOTS =====================================*/

/*===================================== PRIVATE SLOTS ====================================*/

/*======================================= PROTECTED ======================================*/

/*======================================== PRIVATE =======================================*/

void SourceParser::IndexDir(QString pDir)
{
    QDir tFuncDir = pDir;
    QStringList tDirs = tFuncDir.entryList(QDir::Dirs | QDir::NoSymLinks |
                                           QDir::NoDotAndDotDot);
    if (!tDirs.isEmpty()) {
        qDebug() << "Dirs:";
        foreach(QString rDir, tDirs) {
            QString tDir = tFuncDir.path() + '/' + rDir;
            mDirList << new QDir(tDir);
            qDebug() << tDir;
        }
    }

    QStringList tFiles = tFuncDir.entryList(QStringList() << "*.h" << "*.hpp"
                                            << "*.c" << "*.cc" << "*.cpp",
                                            QDir::Files | QDir::NoSymLinks);
    if (!tFiles.isEmpty()) {
        qDebug() << "Files:";
        foreach(QString rFile, tFiles) {
            QString tFile = tFuncDir.path() + '/' + rFile;
            mFileList << new QFile(tFile);
            qDebug() << tFile;
        }
    }
}

/*========================================================================================*/
