/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef QPLATFORMWINDOW_H
#define QPLATFORMWINDOW_H


#include <QtCore/qscopedpointer.h>
#include <QtCore/qrect.h>
#include <QtCore/qstring.h>
#include <QtGui/qwindowdefs.h>


QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

class QPlatformWindowPrivate;
class QWidget;
class QPlatformGLContext;

class Q_GUI_EXPORT QPlatformWindow
{
    Q_DECLARE_PRIVATE(QPlatformWindow)
public:
    QPlatformWindow(QWidget *tlw);
    QPlatformWindow(Qt::HANDLE , QWidget *tlw);
    virtual ~QPlatformWindow();

    QWidget *widget() const;
    virtual void setGeometry(const QRect &rect);
    virtual QRect geometry() const;

    virtual void setVisible(bool visible);
    virtual Qt::WindowFlags setWindowFlags(Qt::WindowFlags flags);
    virtual Qt::WindowFlags windowFlags() const;
    virtual WId winId() const;
    virtual void setParent(const QPlatformWindow *window);

    virtual void setWindowTitle(const QString &title);
    virtual void raise();
    virtual void lower();

    virtual void setOpacity(qreal level);
    virtual void requestActivateWindow();

    virtual QPlatformGLContext *glContext() const;
protected:
    QScopedPointer<QPlatformWindowPrivate> d_ptr;
private:
    Q_DISABLE_COPY(QPlatformWindow)
};

QT_END_NAMESPACE

QT_END_HEADER
#endif //QPLATFORMWINDOW_H
