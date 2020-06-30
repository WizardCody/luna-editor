/*******************************************************************************************
**
** Project: Luna Editor
** File: LunaEditor.cpp
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

#include "Memory.h"
#include "MainWindow.h"
#include "OptionsWindow.h"

#include <QtCore/QTranslator>
#include <QtCore/QSettings>
#include <QtCore/QDir>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

/*======================================== GLOBAL ========================================*/

int main(int argc, char *argv[])
{
    QApplication mApp(argc, argv);
    Memory mHost(&mApp, "LUNAEDITOR-9567143X");

    QStringList tArguments = mApp.arguments();
    tArguments.takeFirst();

    // debug step takes a priority
    #ifdef Q_OS_WIN
    foreach(QString rArgument, tArguments) {
        if (rArgument == "debug") {
            AllocConsole();
            freopen("CONOUT$", "w", stdout);
            freopen("CONIN$", "r", stdin);
            std::ios::sync_with_stdio();
        }
    }
    #endif

    QDir::setCurrent(QApplication::applicationDirPath());
    QSettings *mSettings = new QSettings("settings.ini", QSettings::IniFormat);

    if (mSettings->value("instanceType", 0).toInt() == 0 && mHost.IsRunning()) {
        mHost.SendMessages(tArguments);
        return 0;
    }

    QTranslator tTranslator;
    tTranslator.load(QString("Data/Languages/")
                     .append(mSettings->value("language", "english").toString())
                     .append(".qm"));
    mApp.installTranslator(&tTranslator);

    MainWindow *mMainWindow = MainWindow::Instance();
    mMainWindow->setObjectName(QString::fromUtf8("mMainWindow"));
    mMainWindow->GetOptionsWindow()->SetSettings(mSettings);
    mMainWindow->show();

    QObject::connect(&mHost, SIGNAL(MessageAvailable(QStringList)),
                     mMainWindow, SLOT(OpenDocuments(QStringList)));

    if (mMainWindow->OpenDocuments(tArguments) <= 0)
        mMainWindow->NewDocument();

    return mApp.exec();
}

/*========================================================================================*/
