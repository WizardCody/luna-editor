/*******************************************************************************************
**
** Project: Luna Editor
** File: XmlReader.cpp
**
** Copyright (C) 2014 techvoid.
** All rights reserved.
** Contact: Techvoid (contact@techvoid.net)
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

#include "XmlReader.h"

#include <QtGui/QApplication>
#include <QtGui/QStandardItemModel>
#include <QtGui/QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtXml/QDomDocument>

/*======================================== PUBLIC ========================================*/

XmlReader::XmlReader(QWidget *pParent) :
    QObject(pParent),
    rParentWidget(pParent),
    mDocument(0)
{
}

XmlReader::~XmlReader()
{
    if (mDocument)
        delete mDocument;
}

bool XmlReader::LoadFile(const QString &pFileName)
{
    QDir::setCurrent(QApplication::applicationDirPath());
    QFile tFile(pFileName);
    if (!tFile.open(QFile::ReadOnly)) {
        QMessageBox::information(rParentWidget, tr("information"),
                                 tr("Cannot load \"%1\"\n%2.").
                                 arg(pFileName).arg(tFile.errorString()));
        return false;
    }

    if (mDocument)
        delete mDocument;
    mDocument = new QDomDocument(pFileName);

    mFileName = pFileName;
    mLoaded = true;
    QString tErrorStr;
    int tErrorLine;
    int tErrorColumn;

    if (!mDocument->setContent(&tFile, true, &tErrorStr, &tErrorLine, &tErrorColumn)) {
        tFile.close();
        QMessageBox::information(rParentWidget, tr("information"),
                                 tr("Parse error at line %1, column %2:\n%3")
                                 .arg(tErrorLine).arg(tErrorColumn).arg(tErrorStr));
        return false;
    }

    QDomElement tRoot = mDocument->documentElement();
    if (tRoot.tagName() != "completer") {
        QMessageBox::information(rParentWidget, tr("information"),
                                 tr("%1 is not an auto-completer file.").arg(pFileName));
        return false;
    }

    return true;
}

bool XmlReader::ReloadFile()
{
    if (IsLoaded())
        if (LoadFile(mFileName))
            return true;

    return false;
}

bool XmlReader::SaveFile(const QString &pFileName)
{
    QDir::setCurrent(QApplication::applicationDirPath());
    QFile tFile(pFileName);
    if (!tFile.open(QFile::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::information(rParentWidget, tr("information"),
                                 tr("Cannot save \"%1\"\n%2.").
                                 arg(pFileName).arg(tFile.errorString()));
        return false;
    }

    QTextStream tStream(&tFile);
    mDocument->save(tStream, 5);

    return true;
}

bool XmlReader::ResaveFile()
{
    if (IsLoaded())
        if (SaveFile(mFileName))
            return true;

    return false;
}

void XmlReader::AppendCode(QString &pFuncName, const QString &pFuncHint)
{
    if (!IsLoaded()) return;

    QDomElement tRoot = mDocument->documentElement();
    if (tRoot.tagName() != "completer") return;

    QDomElement tCodeEntries = tRoot.firstChildElement("code");
    if (tCodeEntries.isNull()) {
        tCodeEntries = mDocument->createElement("code");
        tRoot.appendChild(tCodeEntries);
    }

    QDomElement tEntryElement = tCodeEntries.firstChildElement("entry");
    while (!tEntryElement.isNull()) {
        QString tName = tEntryElement.attribute("name");
        if (!tName.isEmpty()) {
            QString tTip = tEntryElement.firstChildElement("hint").text();
            if (tName == pFuncName && tTip == pFuncHint)
                return;
        }
        tEntryElement = tEntryElement.nextSiblingElement("entry");
    }

    QDomElement tCode = mDocument->createElement("entry");
    tCode.setAttribute("name", pFuncName);

    QDomElement tCodeIcon = mDocument->createElement("icon");
    QDomText tCodeIconT = mDocument->createTextNode("Data/Resources/function.png");
    tCodeIcon.appendChild(tCodeIconT);
    tCode.appendChild(tCodeIcon);

    if (!pFuncHint.isEmpty()) {
        QDomElement tHint = mDocument->createElement("hint");
        QDomText tHintT = mDocument->createTextNode(pFuncHint);
        tHint.appendChild(tHintT);
        tCode.appendChild(tHint);
    }

    tCodeEntries.appendChild(tCode);
}

void XmlReader::ClearCode()
{
    if (!IsLoaded()) return;

    QDomElement tRoot = mDocument->documentElement();
    if (tRoot.tagName() != "completer") return;

    QDomElement tCode = tRoot.firstChildElement("code");
    tRoot.removeChild(tCode);
}

QAbstractItemModel *XmlReader::GetModel(QObject *pParent)
{
    QStandardItemModel *rModel = new QStandardItemModel(pParent);

    if (!IsLoaded())
        return rModel;

    QDomElement tRoot = mDocument->documentElement();
    if (tRoot.tagName() != "completer")
        return rModel;

    QDomElement tStdEntries = tRoot.firstChildElement("standard");
    CheckEntries(rModel, tStdEntries);
    QDomElement tCodeEntries = tRoot.firstChildElement("code");
    CheckEntries(rModel, tCodeEntries);

    rModel->sort(0);
    return rModel;
}

/*===================================== PUBLIC SLOTS =====================================*/

/*===================================== PRIVATE SLOTS ====================================*/

/*======================================= PROTECTED ======================================*/

/*======================================== PRIVATE =======================================*/

void XmlReader::CheckEntries(QStandardItemModel *pModel, QDomElement &pElement)
{
    if (!IsLoaded()) return;

    QDomElement tEntryElement = pElement.firstChildElement("entry");
    while (!tEntryElement.isNull()) {
        QString tName = tEntryElement.attribute("name");
        if (!tName.isEmpty()) {
            QStandardItem *tItem = new QStandardItem(tName);
            tItem->setEditable(false);
            pModel->appendRow(tItem);

            QString tIcon = tEntryElement.firstChildElement("icon").text();
            if (!tIcon.isEmpty())
                pModel->setData(tItem->index(), QIcon(tIcon), Qt::DecorationRole);

            QString tTip = tEntryElement.firstChildElement("hint").text();
            if (!tTip.isEmpty())
                pModel->setData(tItem->index(), tTip, Qt::ToolTipRole);
        }
        tEntryElement = tEntryElement.nextSiblingElement("entry");
    }
}

/*========================================================================================*/
