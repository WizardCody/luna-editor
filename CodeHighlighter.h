/*******************************************************************************************
**
** Project: Luna Editor
** File: CodeHighlighter.h
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

#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QtGui/QSyntaxHighlighter>

/*======================================== CLASSES =======================================*/

QT_BEGIN_NAMESPACE
class QTextCharFormat;
class QTextDocument;
class QRegExp;
QT_END_NAMESPACE

class CodeHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

    public:
        CodeHighlighter(QTextDocument *pParent = 0);

    protected:
        void highlightBlock(const QString &pText);

    private:
        struct HighlightingRule {
            QRegExp pattern;
            QTextCharFormat format;
        };
        QVector<HighlightingRule> mHighlightingRules;

        QRegExp mCommentStartExpression;
        QRegExp mCommentEndExpression;

        QTextCharFormat mKeywordFormat;
        QTextCharFormat mNumberFormat;
        QTextCharFormat mQuotationFormat;
        QTextCharFormat mFunctionFormat;
        QTextCharFormat mSingleLineCommentFormat;
        QTextCharFormat mMultiLineCommentFormat;
};

#endif // HIGHLIGHTER_H

/*========================================================================================*/
