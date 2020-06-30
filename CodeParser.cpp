/*******************************************************************************************
**
** Project: Luna Editor
** File: CodeParser.cpp
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

#include "CodeParser.h"

#include <QtGui/QApplication>
#include <QtGui/QStandardItemModel>
#include <QtGui/QStandardItem>
#include <QtGui/QCompleter>
#include <QtCore/QRegExp>

#include "CodeEdit.h"

/*======================================== PUBLIC ========================================*/

CodeParser::CodeParser(CodeEdit *pEditor) :
    QObject(pEditor),
    rEditor(pEditor)
{
}

void CodeParser::ParseText(const QString &pText)
{
    QStringList tLocalList;
    QStringList tFunctionList;

    QRegExp tLocalExp("(?:local[ \\t]+)(\\b\\w+\\b)(?=\\s)");
    QRegExp tFunctionExp("(?:function[ \\t]+)(\\b\\w+\\b)(?=\\s)");

    int tPos = 0;
    while ((tPos = tLocalExp.indexIn(pText, tPos)) != -1) {
        tLocalList << tLocalExp.cap(1);
        tPos += tLocalExp.matchedLength();
    }

    tPos = 0;
    while ((tPos = tFunctionExp.indexIn(pText, tPos)) != -1) {
        tFunctionList << tFunctionExp.cap(1);
        tPos += tFunctionExp.matchedLength();
    }

    //-- Remove old
    foreach(QStandardItem *rItem, mItemList) {
        rModel->removeRow(rItem->index().row());
        mItemList.removeAt(mItemList.indexOf(rItem));
    }

    QStandardItem *tItem;
    QFont tFont;
    tFont.setBold(true);

    foreach(QString rFind, tLocalList) {
        if (rModel->findItems(rFind).count() <= 0) {
            tItem = new QStandardItem(rFind);
            tItem->setIcon(QIcon("Data/Resources/local.png"));
            tItem->setFont(tFont);
            tItem->setEditable(false);
            mItemList.append(tItem);
            rModel->appendRow(tItem);
        }
    }

    foreach(QString rFind, tFunctionList) {
        if (rModel->findItems(rFind).count() <= 0) {
            tItem = new QStandardItem(rFind);
            tItem->setIcon(QIcon("Data/Resources/functionF.png"));
            tItem->setFont(tFont);
            tItem->setEditable(false);
            mItemList.append(tItem);
            rModel->appendRow(tItem);
        }
    }

    rModel->sort(0);
}

void CodeParser::SetModel(QAbstractItemModel *pModel)
{
    rModel = qobject_cast<QStandardItemModel *>(pModel);
    mItemList.clear();
}

/*===================================== PUBLIC SLOTS =====================================*/

/*===================================== PRIVATE SLOTS ====================================*/

/*======================================= PROTECTED ======================================*/

/*======================================== PRIVATE =======================================*/

/*========================================================================================*/
