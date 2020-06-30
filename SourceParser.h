/*******************************************************************************************
**
** Project: Luna Editor
** File: SourceParser.h
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

#ifndef SOURCEPARSER_H
#define SOURCEPARSER_H

#include <QtCore/QObject>

/*======================================== CLASSES =======================================*/

QT_BEGIN_NAMESPACE
class QString;
class QFile;
class QDir;
QT_END_NAMESPACE

class XmlReader;
class CodeEdit;

class SourceParser : public QObject
{
    typedef struct {
        QString Name;
        QString Hint;
    } Function;

    public:
        SourceParser(QWidget *pParent);
        SourceParser(QWidget *pParent, XmlReader *pReader);

        void ParseDir(QString pDir);
        void ParseFile(QString pFile);

        void SetXmlReader(XmlReader *pReader) { rXmlReader = pReader; }
        XmlReader *GetXmlReader() const { return rXmlReader; }

        void SetParentWidget(QWidget *pWidget) { rParentWidget = pWidget; }
        QWidget *GetParentWidget() const { return rParentWidget; }

        void SetEditorList(QList<CodeEdit *> pList);

        void SaveXml();
        void CleanXml();

    private:
        QWidget *rParentWidget;
        XmlReader *rXmlReader;

        void IndexDir(QString pDir);
        QList<QFile *> mFileList;
        QList<QDir *> mDirList;

        QList<CodeEdit *> rEditorList;
};

#endif // SOURCEPARSER_H

/*========================================================================================*/
