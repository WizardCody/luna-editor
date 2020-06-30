/*******************************************************************************************
**
** Project: Luna Editor
** File: StatusBar.h
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

#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QtGui/QStatusBar>

/*======================================== CLASSES =======================================*/

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class StatusBar : public QStatusBar
{
    Q_OBJECT

    public:
        StatusBar(QWidget *pParent = 0);

        QAction *GetToggleAction() const { return mToggleAction; }

        void SetCursorPosition(int pX, int pY);

        void SetFormat(QString pFormat);
        QString GetFormat();

    private slots:
        void UpdateFormat();
        void ToggleVisibility(bool pVisible);

    protected:
        bool event(QEvent *pEvent);

    private:
        QAction *mToggleAction;

        QLabel *mCursorLabel;
        QLabel *mFormatLabel;
};

#endif // STATUSBAR_H

/*========================================================================================*/
