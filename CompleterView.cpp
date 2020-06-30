/*******************************************************************************************
**
** Project: Luna Editor
** File: CompleterView.cpp
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

#include "CompleterView.h"

#include <QtCore/QTimer>
#include <QtCore/QEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QToolTip>

/*======================================== PUBLIC ========================================*/

CompleterView::CompleterView(QWidget *pParent) :
    QListView(pParent)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    //setMouseTracking(true);

    mHintTimer = new QTimer(this);
    mHintTimer->setSingleShot(true);
    connect(mHintTimer, SIGNAL(timeout()), this, SLOT(ShowHint()));
}

/*===================================== PUBLIC SLOTS =====================================*/

/*===================================== PRIVATE SLOTS ====================================*/

void CompleterView::currentChanged(const QModelIndex &pCurrent, const QModelIndex &pPrevious)
{
    if (pCurrent.isValid()) {
        QToolTip::hideText();
        mHintTimer->start(500);
    }

    return QListView::currentChanged(pCurrent, pPrevious);
}

void CompleterView::ShowHint()
{
    QModelIndex tCurrentIndex = currentIndex();
    QRect tRect = visualRect(tCurrentIndex);

    if (!this->isHidden()) {
        QToolTip::showText(QPoint(x() + sizeHintForIndex(tCurrentIndex).width(),
                                  y() + tRect.y()),
                           model()->data(tCurrentIndex, Qt::ToolTipRole).toString());
    }
}

/*======================================= PROTECTED ======================================*/

void CompleterView::mouseMoveEvent(QMouseEvent *pEvent)
{
    //-- requires a mouse tracking
    return QListView::mouseMoveEvent(pEvent);
}

void CompleterView::mouseReleaseEvent(QMouseEvent *pEvent)
{
    if (pEvent->button() != Qt::NoButton) {
        return; //-- ignore clicked() signal
    } else {
        return QListView::mouseReleaseEvent(pEvent);
    }
}

void CompleterView::mouseDoubleClickEvent(QMouseEvent *pEvent)
{
    /** QCompleter class only reacts to a clicked() signal via activated() */
    emit clicked(currentIndex());

    return QListView::mouseDoubleClickEvent(pEvent);
}

bool CompleterView::viewportEvent(QEvent *pEvent)
{
    if (pEvent->type() == QEvent::ToolTip) {
        QToolTip::showText(QCursor::pos(),
                           model()->data(indexAt(mapFromGlobal(QCursor::pos())),
                                         Qt::ToolTipRole).toString());

        return true; //-- means process further
    } else {
        return QListView::viewportEvent(pEvent);
    }
}

/*======================================== PRIVATE =======================================*/

/*========================================================================================*/
