/*******************************************************************************************
**
** Project: Luna Editor
** File: XmlReader.h
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

#ifndef XMLREADER_H
#define XMLREADER_H

#include <QtCore/QObject>

/*======================================== CLASSES =======================================*/

QT_BEGIN_NAMESPACE
class QStandardItemModel;
class QAbstractItemModel;
class QDomDocument;
class QDomElement;
class QString;
class QWidget;
QT_END_NAMESPACE

class XmlReader : public QObject
{
    Q_OBJECT

    public:
        XmlReader(QWidget *pParent = 0);
        ~XmlReader();

        bool LoadFile(const QString &pFileName);
        bool ReloadFile();
        bool SaveFile(const QString &pFileName);
        bool ResaveFile();

        bool IsLoaded() const { return mLoaded; }
        QString GetFileName() const { return mFileName; }

        void SetParentWidget(QWidget *pWidget) { rParentWidget = pWidget; }
        QWidget *GetParentWidget() const { return rParentWidget; }

        void AppendCode(QString &pFuncName, const QString &pFuncHint = QString());
        void ClearCode();

        QAbstractItemModel *GetModel(QObject *pParent = 0);

    private:
        QWidget *rParentWidget;

        bool mLoaded;
        QString mFileName;
        QDomDocument *mDocument;

        void CheckEntries(QStandardItemModel *pModel, QDomElement &pElement);
};

#endif // XMLREADER_H

/*========================================================================================*/
