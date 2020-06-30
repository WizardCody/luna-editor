/*******************************************************************************************
**
** Project: Luna Editor
** File: FinderWindow.cpp
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

#include "FinderWindow.h"

#include "MainWindow.h"
#include "CodeEdit.h"

/*======================================== PUBLIC ========================================*/

FinderWindow::FinderWindow(MainWindow *pParent) :
    QDialog(pParent),
    rMainWindow(pParent)
{
    ui.setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    QObject::connect(ui.mButtonFind, SIGNAL(clicked()), this, SLOT(Find()));
    QObject::connect(ui.mButtonCancel, SIGNAL(clicked()), this, SLOT(reject()));
    ui.mTextNext->setChecked(true);
    ui.mTextCaseSensitive->setChecked(true);
}

QString FinderWindow::GetText() const
{
    return ui.mTextLineEdit->text();
}

/*===================================== PUBLIC SLOTS =====================================*/

bool FinderWindow::Find()
{
    unsigned int tOrder = 0;
    if (ui.mTextPrevious->isChecked())
        tOrder |= (int)QTextDocument::FindBackward;
    if (ui.mTextCaseSensitive->isChecked())
        tOrder |= (int)QTextDocument::FindCaseSensitively;

    if (rMainWindow->GetCurrentDocument()->find(GetText(),
            (QTextDocument::FindFlag)tOrder))
        return true;

    return false;
}

/*===================================== PRIVATE SLOTS ====================================*/

/*======================================= PROTECTED ======================================*/

void FinderWindow::changeEvent(QEvent *pEvent)
{
    if (pEvent->type() == QEvent::LanguageChange) {
        // translate
    }
    QDialog::changeEvent(pEvent);
}

/*======================================== PRIVATE =======================================*/

/*========================================================================================*/
