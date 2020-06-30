/*******************************************************************************************
**
** Project: Luna Editor
** File: Memory.h
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

/**
** This class was supposed to derive from QApplication. Sadly, it was causing problems on
** the Linux, so it is now a separate class.
** The problem was that it couldn't hold the application in main() function, instantly
** closing it and returning the -1 value.
*/

/*======================================== HEADERS =======================================*/

#ifndef MEMORY_H
#define MEMORY_H

#include <QtCore/QObject>

/*======================================== CLASSES =======================================*/

QT_BEGIN_NAMESPACE
class QStringList;
class QSharedMemory;
QT_END_NAMESPACE

class Memory : public QObject
{
    Q_OBJECT

    public:
        Memory(QObject *parent, const QString &pUniqueKey);

        bool IsRunning() const { return mIsRunning; }

        bool SendMessage(const QString &pMessage);
        int SendMessages(const QStringList &pMessages);

    public slots:
        void CheckForMessage();

    signals:
        void MessageAvailable(const QStringList &pMessages);

    private:
        bool mIsRunning;
        QSharedMemory *mSharedMemory;
};

#endif // MEMORY_H

/*========================================================================================*/
