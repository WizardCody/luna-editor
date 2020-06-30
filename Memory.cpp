/*******************************************************************************************
**
** Project: Luna Editor
** File: Memory.cpp
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

#include <QtCore/QTimer>
#include <QtCore/QByteArray>
#include <QtCore/QStringList>
#include <QtCore/QSharedMemory>

/*======================================== PUBLIC ========================================*/

Memory::Memory(QObject *parent, const QString &pUniqueKey) :
    QObject(parent)
{
    mSharedMemory = new QSharedMemory(this);
    mSharedMemory->setKey(pUniqueKey);

    // when can create it only if it doesn't exist
    if (mSharedMemory->create(5000)) {
        mSharedMemory->lock();
        *(char *)mSharedMemory->data() = '\0';
        mSharedMemory->unlock();

        mIsRunning = false;

        // start checking for messages of other instances.
        QTimer *rTimer = new QTimer(this);
        connect(rTimer, SIGNAL(timeout()), this, SLOT(CheckForMessage()));
        rTimer->start(200);
    }
    // it exits, so we can attach it?!
    else if (mSharedMemory->attach()) {
        mIsRunning = true;
    } else {
        // error
    }
}

bool Memory::SendMessage(const QString &pMessage)
{
    //we cannot send mess if we are master process!
    if (!IsRunning())
        return false;

    QByteArray tByteArray;
    tByteArray.append(char(pMessage.size()));
    tByteArray.append(pMessage.toUtf8());
    tByteArray.append('\0');

    mSharedMemory->lock();
    char *rTo = (char *)mSharedMemory->data();
    while (*rTo != '\0') {
        int sizeToRead = int(*rTo);
        rTo += sizeToRead + 1;
    }

    const char *rFrom = tByteArray.data();
    memcpy(rTo, rFrom, qMin(mSharedMemory->size(), tByteArray.size()));
    mSharedMemory->unlock();

    return true;
}

int Memory::SendMessages(const QStringList &pMessages)
{
    int tSuccess = 0;
    foreach(QString rMessage, pMessages) {
        if (SendMessage(rMessage))
            tSuccess++;
    }
    return tSuccess;
}

/*===================================== PUBLIC SLOTS =====================================*/

void Memory::CheckForMessage()
{
    QStringList tArguments;

    mSharedMemory->lock();
    char *rFrom = (char *)mSharedMemory->data();

    while (*rFrom != '\0') {
        int sizeToRead = int(*rFrom);
        ++rFrom;

        QByteArray tByteArray = QByteArray(rFrom, sizeToRead);
        tByteArray[sizeToRead] = '\0';
        rFrom += sizeToRead;

        tArguments << QString::fromUtf8(tByteArray.constData());
    }

    *(char *)mSharedMemory->data() = '\0';
    mSharedMemory->unlock();

    if (tArguments.size()) emit MessageAvailable( tArguments );
}

/*===================================== PRIVATE SLOTS ====================================*/

/*======================================= PROTECTED ======================================*/

/*======================================== PRIVATE =======================================*/

/*========================================================================================*/
