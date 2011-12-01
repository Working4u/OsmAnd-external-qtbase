/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the plugins of the Qt Toolkit.
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

#ifndef COMPLEXWIDGETS_H
#define COMPLEXWIDGETS_H

#include <QtCore/qpointer.h>
#include <QtWidgets/qaccessiblewidget.h>
#include <QtWidgets/qabstractitemview.h>
#include <QtGui/qaccessible2.h>

QT_BEGIN_NAMESPACE

#ifndef QT_NO_ACCESSIBILITY

class QAbstractButton;
class QHeaderView;
class QTabBar;
class QComboBox;
class QTitleBar;
class QAbstractScrollArea;
class QScrollArea;

#ifndef QT_NO_SCROLLAREA
class QAccessibleAbstractScrollArea : public QAccessibleWidget
{
public:
    explicit QAccessibleAbstractScrollArea(QWidget *widget);

    enum AbstractScrollAreaElement {
        Self = 0,
        Viewport,
        HorizontalContainer,
        VerticalContainer,
        CornerWidget,
        Undefined
    };

    QAccessibleInterface *child(int index) const;
    QVariant invokeMethod(QAccessible::Method method, const QVariantList &params);
    int childCount() const;
    int indexOfChild(const QAccessibleInterface *child) const;
    bool isValid() const;
    int navigate(QAccessible::RelationFlag relation, int entry, QAccessibleInterface **target) const;
    QAccessibleInterface *childAt(int x, int y) const;

//protected:
    QAbstractScrollArea *abstractScrollArea() const;

private:
    QWidgetList accessibleChildren() const;
    AbstractScrollAreaElement elementType(QWidget *widget) const;
    bool isLeftToRight() const;
};

class QAccessibleScrollArea : public QAccessibleAbstractScrollArea
{
public:
    explicit QAccessibleScrollArea(QWidget *widget);
};
#endif // QT_NO_SCROLLAREA

#ifndef QT_NO_TABBAR
class QAccessibleTabBar : public QAccessibleWidget
{
public:
    explicit QAccessibleTabBar(QWidget *w);

    int childCount() const;
    QString text(QAccessible::Text t) const;

    bool setSelected(int child, bool on, bool extend);
    QVector<int> selection() const;

    QAccessibleInterface* child(int index) const;
    int indexOfChild(const QAccessibleInterface *child) const;
    int navigate(QAccessible::RelationFlag rel, int entry, QAccessibleInterface **target) const;

protected:
    QTabBar *tabBar() const;
};
#endif // QT_NO_TABBAR

#ifndef QT_NO_COMBOBOX
class QAccessibleComboBox : public QAccessibleWidget
{
public:
    explicit QAccessibleComboBox(QWidget *w);

    int childCount() const;
    QAccessibleInterface *childAt(int x, int y) const;
    int indexOfChild(const QAccessibleInterface *child) const;
    QAccessibleInterface* child(int index) const;

    QString text(QAccessible::Text t) const;

    // QAccessibleActionInterface
    QStringList actionNames() const;
    QString localizedActionDescription(const QString &actionName) const;
    void doAction(const QString &actionName);
    QStringList keyBindingsForAction(const QString &actionName) const;

protected:
    QComboBox *comboBox() const;
};
#endif // QT_NO_COMBOBOX

#endif // QT_NO_ACCESSIBILITY

QT_END_NAMESPACE

#endif // COMPLEXWIDGETS_H
