/*******************************************************************************************
**
** Project: Luna Editor
** File: CodeParser.h
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

#ifndef CODEPARSER_H
#define CODEPARSER_H

#include <QtCore/QObject>
#include <QtCore/QList>

/*======================================== CLASSES =======================================*/

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
class QStandardItemModel;
class QStandardItem;
QT_END_NAMESPACE

class CodeEdit;

class CodeParser : public QObject
{

    public:
        CodeParser(CodeEdit *pEditor);

        void ParseText(const QString &pText = QString());

        void SetModel(QAbstractItemModel *pModel);
        QStandardItemModel *GetModel() const { return rModel; }

        void SetEditor(CodeEdit *pEditor) { rEditor = pEditor; }
        CodeEdit *GetEditor() const { return rEditor; }

    private:
        CodeEdit *rEditor;

        QStandardItemModel *rModel;
        QList<QStandardItem *> mItemList;
};

#endif // CODEPARSER_H

/*========================================================================================*/
