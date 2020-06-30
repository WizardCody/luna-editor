/*******************************************************************************************
**
** Project: Luna Editor
** File: CompleterView.h
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

#ifndef COMPLETERVIEW_H
#define COMPLETERVIEW_H

#include <QtGui/QListView>

/*======================================== CLASSES =======================================*/

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

class CompleterView : public QListView
{
    Q_OBJECT

    public:
        CompleterView(QWidget *pParent = 0);

    private slots:
        void currentChanged(const QModelIndex &pCurrent,
                            const QModelIndex &pPrevious);
        void ShowHint();

    protected:
        void mouseMoveEvent(QMouseEvent *pEvent);
        void mouseReleaseEvent(QMouseEvent *pEvent);
        void mouseDoubleClickEvent(QMouseEvent *pEvent);
        bool viewportEvent(QEvent *pEvent);

    private:
        QTimer *mHintTimer;
};

#endif // COMPLETERVIEW_H

/*========================================================================================*/
