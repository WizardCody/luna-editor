/*******************************************************************************************
**
** Project: Luna Editor
** File: StatusBar.cpp
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

#include "StatusBar.h"

#include <QtGui/QAction>
#include <QtGui/QLabel>
#include <QtCore/QEvent>

/*======================================== PUBLIC ========================================*/

StatusBar::StatusBar(QWidget *pParent) :
    QStatusBar(pParent)
{
    mToggleAction = new QAction(this);
    mToggleAction->setCheckable(true);
    mToggleAction->setText(tr("&Status Bar"));
    connect(mToggleAction, SIGNAL(toggled(bool)),
            this, SLOT(ToggleVisibility(bool)));

    setStyleSheet(
        "QStatusBar::item { border: none; }"
    );

    mCursorLabel = new QLabel(this);
    mCursorLabel->setAlignment(Qt::AlignRight);
    addPermanentWidget(mCursorLabel);

    mFormatLabel = new QLabel(this);
    mFormatLabel->setContextMenuPolicy(Qt::ActionsContextMenu);

    QAction *rAct1, *rAct2;
    mFormatLabel->addAction(rAct1 = new QAction("UTF-8 non-BOM", this));
    connect(rAct1, SIGNAL(triggered()), this, SLOT(UpdateFormat()));
    mFormatLabel->addAction(rAct2 = new QAction("UTF-8 BOM", this));
    connect(rAct2, SIGNAL(triggered()), this, SLOT(UpdateFormat()));
    mFormatLabel->setAlignment(Qt::AlignRight);
    addPermanentWidget(mFormatLabel);

    SetFormat("UTF-8 non-BOM"); // std for every file
}

void StatusBar::SetCursorPosition(int pX, int pY)
{
    mCursorLabel->setText(QString::number(pX) + ", " + QString::number(pY));
}

void StatusBar::SetFormat(QString pFormat)
{
    mFormatLabel->setText(pFormat);
}

QString StatusBar::GetFormat()
{
    return mFormatLabel->text();
}

/*===================================== PUBLIC SLOTS =====================================*/

/*===================================== PRIVATE SLOTS ====================================*/

void StatusBar::UpdateFormat()
{
    QAction *rAct = qobject_cast<QAction *>(sender());
    SetFormat(rAct->text());
}

void StatusBar::ToggleVisibility(bool pVisible)
{
    setVisible(pVisible);
}

/*======================================= PROTECTED ======================================*/

bool StatusBar::event(QEvent *pEvent)
{
    if (pEvent->type() == QEvent::Show) {
        mToggleAction->setChecked(true);
    } else if (pEvent->type() == QEvent::Hide) {
        mToggleAction->setChecked(false);
    }

    return QStatusBar::event(pEvent);
}

/*======================================== PRIVATE =======================================*/

/*========================================================================================*/
