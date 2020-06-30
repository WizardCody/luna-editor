/*******************************************************************************************
**
** Project: Luna Editor
** File: LineNumberArea.cpp
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

#include "LineNumberArea.h"

#include <QtGui/QPainter>
#include <QtGui/QTextBlock>

#include "CodeEdit.h"

/*======================================== PUBLIC ========================================*/

LineNumberArea::LineNumberArea(CodeEdit *pEditor) :
    QWidget(pEditor),
    rEditor(pEditor)
{
}

int LineNumberArea::GetAreaWidth() const
{
    int tDigits = 1;
    int tMax = qMax(1, rEditor->blockCount());
    while (tMax >= 10) {
        tMax /= 10;
        ++tDigits;
    }

    int tSpace = 3 + rEditor->fontMetrics().width(QLatin1Char('9')) * tDigits;

    return tSpace;
}

QSize LineNumberArea::sizeHint() const
{
    return QSize(GetAreaWidth(), 0);
}

/*===================================== PUBLIC SLOTS =====================================*/

/*===================================== PRIVATE SLOTS ====================================*/

/*======================================= PROTECTED ======================================*/

void LineNumberArea::paintEvent(QPaintEvent *pEvent)
{
    QPainter tPainter(this);
    tPainter.fillRect(pEvent->rect(), Qt::lightGray);

    QTextBlock tBlock = rEditor->firstVisibleBlock();
    int tBlockNumber = tBlock.blockNumber();
    int tTop = (int)rEditor->blockBoundingGeometry(tBlock).
               translated(rEditor->contentOffset()).top();
    int tBottom = tTop + (int) rEditor->blockBoundingRect(tBlock).height();

    while (tBlock.isValid() && tTop <= pEvent->rect().bottom()) {
        if (tBlock.isVisible() && tBottom >= pEvent->rect().top()) {
            QString tNumber = QString::number(tBlockNumber + 1);
            tPainter.setPen(Qt::black);
            tPainter.drawText(0, tTop, width(), fontMetrics().height(),
                              Qt::AlignRight, tNumber);
        }

        tBlock = tBlock.next();
        tTop = tBottom;
        tBottom = tTop + (int)rEditor->blockBoundingRect(tBlock).height();
        ++tBlockNumber;
    }
}

/*======================================== PRIVATE =======================================*/

/*========================================================================================*/
