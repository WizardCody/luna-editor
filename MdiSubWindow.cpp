/*******************************************************************************************
**
** Project: Luna Editor
** File: MdiSubWindow.cpp
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

#include "MdiSubWindow.h"

#include <QtGui/QApplication>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDragMoveEvent>
#include <QtGui/QDragLeaveEvent>
#include <QtGui/QMenu>
#include <QtCore/QUrl>
#include <QtCore/QFileInfo>

#include "MainWindow.h"
#include "CodeEdit.h"

/*======================================== PUBLIC ========================================*/

MdiSubWindow::MdiSubWindow(QWidget *pParent) :
    QMdiSubWindow(pParent)
{
    //rEditor = qobject_cast<CodeEdit*>(widget());
    setWindowIcon(QIcon("Data/Resources/script.png"));
    setAttribute(Qt::WA_DeleteOnClose);
    setAcceptDrops(true);

    SetupMenu();
}

void MdiSubWindow::SetEditor(CodeEdit *pEditor)
{
    rEditor = pEditor;
    setWidget(pEditor);
}

/*===================================== PUBLIC SLOTS =====================================*/

void MdiSubWindow::Close()
{
    MainWindow::Instance()->CloseDocument(rEditor->GetFilePath());
}

void MdiSubWindow::CloseAll()
{
    MainWindow::Instance()->CloseAll();
}

void MdiSubWindow::CloseAllOthers()
{
    MainWindow::Instance()->CloseAllOthers(rEditor->GetFilePath());
}

void MdiSubWindow::Replace()
{
    MainWindow::Instance()->ReplaceDocument(rEditor->GetFilePath());
}

/*===================================== PRIVATE SLOTS ====================================*/

/*======================================= PROTECTED ======================================*/


void MdiSubWindow::dragEnterEvent(QDragEnterEvent *pEvent)
{
    pEvent->acceptProposedAction();
}

void MdiSubWindow::dragMoveEvent(QDragMoveEvent *pEvent)
{
    pEvent->acceptProposedAction();
}

void MdiSubWindow::dragLeaveEvent(QDragLeaveEvent *pEvent)
{
    pEvent->accept();
}

void MdiSubWindow::dropEvent(QDropEvent *pEvent)
{
    const QMimeData *tMimeData = pEvent->mimeData();
    if (tMimeData->hasUrls()) {
        QList<QUrl> tUrlList = tMimeData->urls();
        QString tFile = QFileInfo(tUrlList.at(0).toLocalFile()).canonicalFilePath();
        if (MainWindow::Instance()->ReplaceDocument(rEditor->GetFilePath(), tFile));
            pEvent->acceptProposedAction();
    }
}

/*======================================== PRIVATE =======================================*/

void MdiSubWindow::SetupMenu()
{
    QMenu *rWindowMenu = new QMenu(this);
    rWindowMenu->addAction(tr("Close"), this, SLOT(Close()));
    rWindowMenu->addAction(tr("Close all"), this, SLOT(CloseAll()));
    rWindowMenu->addAction(tr("Close all except this"), this, SLOT(CloseAllOthers()));
    rWindowMenu->addSeparator();
    rWindowMenu->addAction(tr("Replace with..."), this, SLOT(Replace()));
    setSystemMenu(rWindowMenu);
}

/*========================================================================================*/
