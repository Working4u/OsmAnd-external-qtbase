/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QtTest/QtTest>

#include <QCoreApplication>
#include <QWriteLocker>
#include <QSemaphore>
#include <QThread>

//TESTED_CLASS=
//TESTED_FILES=

class tst_QWriteLockerThread : public QThread
{
public:
    QReadWriteLock lock;
    QSemaphore semaphore, testSemaphore;

    void waitForTest()
    {
        semaphore.release();
        testSemaphore.acquire();
    }
};

class tst_QWriteLocker : public QObject
{
    Q_OBJECT

public:
    tst_QWriteLocker();
    ~tst_QWriteLocker();

    tst_QWriteLockerThread *thread;

    void waitForThread()
    {
        thread->semaphore.acquire();
    }
    void releaseThread()
    {
        thread->testSemaphore.release();
    }

private slots:
    void scopeTest();
    void unlockAndRelockTest();
    void lockerStateTest();
};

tst_QWriteLocker::tst_QWriteLocker()
{
}

tst_QWriteLocker::~tst_QWriteLocker()
{
}

void tst_QWriteLocker::scopeTest()
{
    class ScopeTestThread : public tst_QWriteLockerThread
    {
    public:
        void run()
        {
            waitForTest();

            {
                QWriteLocker locker(&lock);
                waitForTest();
            }

            waitForTest();
        }
    };

    thread = new ScopeTestThread;
    thread->start();

    waitForThread();
    // lock should be unlocked before entering the scope that creates the QWriteLocker
    QVERIFY(thread->lock.tryLockForWrite());
    thread->lock.unlock();
    releaseThread();

    waitForThread();
    // lock should be locked by the QWriteLocker
    QVERIFY(!thread->lock.tryLockForWrite());
    releaseThread();

    waitForThread();
    // lock should be unlocked when the QWriteLocker goes out of scope
    QVERIFY(thread->lock.tryLockForWrite());
    thread->lock.unlock();
    releaseThread();

    QVERIFY(thread->wait());

    delete thread;
    thread = 0;
}


void tst_QWriteLocker::unlockAndRelockTest()
{
    class UnlockAndRelockThread : public tst_QWriteLockerThread
    {
    public:
        void run()
        {
            QWriteLocker locker(&lock);

            waitForTest();

            locker.unlock();

            waitForTest();

            locker.relock();

            waitForTest();
        }
    };

    thread = new UnlockAndRelockThread;
    thread->start();

    waitForThread();
    // lock should be locked by the QWriteLocker
    QVERIFY(!thread->lock.tryLockForWrite());
    releaseThread();

    waitForThread();
    // lock has been explicitly unlocked via QWriteLocker
    QVERIFY(thread->lock.tryLockForWrite());
    thread->lock.unlock();
    releaseThread();

    waitForThread();
    // lock has been explicity relocked via QWriteLocker
    QVERIFY(!thread->lock.tryLockForWrite());
    releaseThread();

    QVERIFY(thread->wait());

    delete thread;
    thread = 0;
}

void tst_QWriteLocker::lockerStateTest()
{
    class LockerStateThread : public tst_QWriteLockerThread
    {
    public:
        void run()
        {
            {
                QWriteLocker locker(&lock);
                locker.relock();
                locker.unlock();

                waitForTest();
            }

            waitForTest();
        }
    };

    thread = new LockerStateThread;
    thread->start();

    waitForThread();
    // even though we relock() after creating the QWriteLocker, it shouldn't lock the lock more than once
    QVERIFY(thread->lock.tryLockForWrite());
    thread->lock.unlock();
    releaseThread();

    waitForThread();
    // if we call QWriteLocker::unlock(), its destructor should do nothing
    QVERIFY(thread->lock.tryLockForWrite());
    thread->lock.unlock();
    releaseThread();

    QVERIFY(thread->wait());

    delete thread;
    thread = 0;
}

QTEST_MAIN(tst_QWriteLocker)
#include "tst_qwritelocker.moc"
