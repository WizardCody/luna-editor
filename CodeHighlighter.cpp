/*******************************************************************************************
**
** Project: Luna Editor
** File: CodeHighlighter.cpp
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

#include "CodeHighlighter.h"

/*======================================== PUBLIC ========================================*/

CodeHighlighter::CodeHighlighter(QTextDocument *pParent)
    : QSyntaxHighlighter(pParent)
{
    HighlightingRule tRule;

    mKeywordFormat.setForeground(Qt::darkBlue);
    mKeywordFormat.setFontWeight(QFont::Bold);
    QStringList tKeywordPatterns;
    tKeywordPatterns << "\\band\\b" << "\\bbreak\\b" << "\\bdo\\b"
                     << "\\belse\\b" << "\\belseif\\b" << "\\bend\\b"
                     << "\\bfalse\\b" << "\\bfor\\b" << "\\bfunction\\b"
                     << "\\bif\\b" << "\\bin\\b" << "\\blocal\\b"
                     << "\\bnil\\b" << "\\bnot\\b" << "\\bor\\b"
                     << "\\brepeat\\b" << "\\breturn\\b" << "\\bthen\\b"
                     << "\\btrue\\b" << "\\buntil\\b" << "\\bwhile\\b";
    foreach(const QString &rPattern, tKeywordPatterns) {
        tRule.pattern = QRegExp(rPattern);
        tRule.format = mKeywordFormat;
        mHighlightingRules.append(tRule);
    }

    mNumberFormat.setForeground(Qt::magenta);
    tRule.pattern = QRegExp("\\b[0-9]+\\b");
    tRule.format = mNumberFormat;
    mHighlightingRules.append(tRule);

    mMultiLineCommentFormat.setForeground(Qt::red);

    mQuotationFormat.setForeground(Qt::darkGreen);
    QRegExp tQuotationExp("\".*\"");
    tQuotationExp.setMinimal(true);
    tRule.pattern = tQuotationExp;
    tRule.format = mQuotationFormat;
    mHighlightingRules.append(tRule);

    mFunctionFormat.setFontItalic(false);
    mFunctionFormat.setForeground(Qt::blue);
    tRule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    tRule.format = mFunctionFormat;
    mHighlightingRules.append(tRule);

    mSingleLineCommentFormat.setForeground(Qt::red);
    tRule.pattern = QRegExp("--[^\n]*");
    tRule.format = mSingleLineCommentFormat;
    mHighlightingRules.append(tRule);

    mCommentStartExpression = QRegExp("--\\[\\[");
    mCommentEndExpression = QRegExp("\\]\\]");
}

/*===================================== PUBLIC SLOTS =====================================*/

/*===================================== PRIVATE SLOTS ====================================*/

/*======================================= PROTECTED ======================================*/

void CodeHighlighter::highlightBlock(const QString &pText)
{
    foreach (const HighlightingRule &rRule, mHighlightingRules) {
        QRegExp tExpression(rRule.pattern);
        int tIndex = tExpression.indexIn(pText);
        while (tIndex >= 0) {
            int tLength = tExpression.matchedLength();
            setFormat(tIndex, tLength, rRule.format);
            tIndex = tExpression.indexIn(pText, tIndex + tLength);
        }
    }

    setCurrentBlockState(0);

    int tStartIndex = 0;
    if (previousBlockState() != 1)
        tStartIndex = mCommentStartExpression.indexIn(pText);

    while (tStartIndex >= 0) {

        int tEndIndex = mCommentEndExpression.indexIn(pText, tStartIndex);
        int tCommentLength;
        if (tEndIndex == -1) {
            setCurrentBlockState(1);
            tCommentLength = pText.length() - tStartIndex;
        } else {
            tCommentLength = tEndIndex - tStartIndex
                             + mCommentEndExpression.matchedLength();
        }
        setFormat(tStartIndex, tCommentLength, mMultiLineCommentFormat);
        tStartIndex = mCommentStartExpression.indexIn(pText, tStartIndex + tCommentLength);
    }
}

/*======================================== PRIVATE =======================================*/

/*========================================================================================*/
