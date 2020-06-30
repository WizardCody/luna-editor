/*******************************************************************************************
**
** Project: Luna Editor
** File: FinderWindow.h
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

#ifndef FINDERWINDOW_H
#define FINDERWINDOW_H

#include <generated/FinderWindow_ui.h>

/*======================================== CLASSES =======================================*/

class MainWindow;

class FinderWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit FinderWindow(MainWindow *pParent);

        QString GetText() const;

    public slots:
        bool Find();

    protected:
        void changeEvent(QEvent *pEvent);

    private:
        Ui_FinderWindow ui;
        MainWindow *rMainWindow;
};

#endif // FINDERWINDOW_H

/*========================================================================================*/
