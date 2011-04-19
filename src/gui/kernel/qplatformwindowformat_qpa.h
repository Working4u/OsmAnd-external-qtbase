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
#ifndef QPLATFORMWINDOWFORMAT_QPA_H
#define QPLATFORMWINDOWFORMAT_QPA_H

#include <QtGui/QPlatformWindow>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

class QWindowFormatPrivate;

class QWindowPrivate;

class Q_GUI_EXPORT QWindow : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QWindow)

    Q_PROPERTY(QString windowTitle READ windowTitle WRITE setWindowTitle)

public:
    void setVisible(bool visible);

    WId winId() const;
    void setParent(const QWindow *window);

    void setWindowTitle(const QString &title);
    void raise();
    void lower();

    void setOpacity(qreal level);
    void requestActivateWindow();

    Qt::WindowStates windowState() const;
    void setWindowState(Qt::WindowStates state);

    QSize minimumSize() const;
    QSize maximumSize() const;

    void setMinimumSize(const QSize &size) const;
    void setMaximumSize(const QSize &size) const;

    void setGeometry(const QRect &rect);
    QRect geometry() const;

    QString windowTitle() const;

    void setWindowIcon(const QImage &icon) const;

    QGLContext *glContext() const;

public Q_SLOTS:
    inline void show() { setVisible(true); }
    inline void hide() { setVisible(false); }

    void showMinimized();
    void showMaximized();
    void showFullScreen();
    void showNormal();

    bool close();
    void raise();
    void lower();

    void setWindowTitle(const QString &);

Q_SIGNALS:
    void backBufferReady();

protected:
    virtual void resizeEvent(QResizeEvent *);

    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

    virtual bool event(QEvent *);
    virtual void keyPressEvent(QKeyEvent *);
    virtual void keyReleaseEvent(QKeyEvent *);
    virtual void inputMethodEvent(QInputMethodEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseDoubleClickEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
#ifndef QT_NO_WHEELEVENT
    virtual void wheelEvent(QWheelEvent *);
#endif

private:
    Q_DISABLE_COPY(QWindow)
};

class Q_GUI_EXPORT QWindowFormat
{
public:
    enum FormatOption {
        StereoBuffers           = 0x0001,
        WindowSurface           = 0x0002
    };
    Q_DECLARE_FLAGS(FormatOptions, FormatOption)

#if 0
    enum WindowType {
        Window = 0x00000001,
        Dialog = 0x00000002,
        Popup = 0x00000004,
        ToolTip = 0x00000008
    };
    Q_DECLARE_FLAGS(WindowTypes, WindowType)
#endif

    enum ColorFormat {
        InvalidColorFormat,
        RGB565,
        RGBA5658,
        RGBA5551,
        RGB888,
        RGBA5658,
    };

    enum SwapBehavior {
        DefaultSwapBehavior,
        SingleBuffer,
        DoubleBuffer,
        TripleBuffer
    };

    enum OpenGLContextProfile {
        NoProfile,
        CoreProfile,
        CompatibilityProfile
    };

    QWindowFormat();
    QWindowFormat(FormatOptions options);
    QWindowFormat(const QWindowFormat &other);
    QWindowFormat &operator=(const QWindowFormat &other);
    ~QWindowFormat();

    void setDepthBufferSize(int size);
    int depthBufferSize() const;

    void setStencilBufferSize(int size);
    int stencilBufferSize() const;

    void setSamples(int numSamples);
    int samples() const;

    void setSwapBehavior(SwapBehavior behavior);
    SwapBehavior swapBehavior() const;

    void setColorFormat(ColorFormat format);
    ColorFormat colorFormat() const;

    void setProfile(OpenGLContextProfile profile);
    OpenGLContextProfile profile() const;

    void setSharedContext(QPlatformGLContext *context);
    QPlatformGLContext *sharedGLContext() const;

    bool depth() const;
    void setDepth(bool enable);
    bool stencil() const;
    void setStencil(bool enable);
    bool stereo() const;
    void setStereo(bool enable);
    bool hasWindowSurface() const;
    void setWindowSurface(bool enable);

    void setOption(QWindowFormat::FormatOptions opt);
    bool testOption(QWindowFormat::FormatOptions opt) const;

private:
    QWindowFormatPrivate *d;

    void detach();

    friend Q_GUI_EXPORT bool operator==(const QWindowFormat&, const QWindowFormat&);
    friend Q_GUI_EXPORT bool operator!=(const QWindowFormat&, const QWindowFormat&);
#ifndef QT_NO_DEBUG_STREAM
    friend Q_GUI_EXPORT QDebug operator<<(QDebug, const QWindowFormat &);
#endif
};

Q_GUI_EXPORT bool operator==(const QWindowFormat&, const QWindowFormat&);
Q_GUI_EXPORT bool operator!=(const QWindowFormat&, const QWindowFormat&);

#ifndef QT_NO_DEBUG_STREAM
Q_OPENGL_EXPORT QDebug operator<<(QDebug, const QWindowFormat &);
#endif

Q_DECLARE_OPERATORS_FOR_FLAGS(QWindowFormat::FormatOptions)
Q_DECLARE_OPERATORS_FOR_FLAGS(QWindowFormat::WindowTypes)

inline bool QWindowFormat::doubleBuffer() const
{
    return testOption(QWindowFormat::DoubleBuffer);
}

inline bool QWindowFormat::depth() const
{
    return testOption(QWindowFormat::DepthBuffer);
}

inline bool QWindowFormat::rgba() const
{
    return testOption(QWindowFormat::Rgba);
}

inline bool QWindowFormat::alpha() const
{
    return testOption(QWindowFormat::AlphaChannel);
}

inline bool QWindowFormat::accum() const
{
    return testOption(QWindowFormat::AccumBuffer);
}

inline bool QWindowFormat::stencil() const
{
    return testOption(QWindowFormat::StencilBuffer);
}

inline bool QWindowFormat::stereo() const
{
    return testOption(QWindowFormat::StereoBuffers);
}

inline bool QWindowFormat::directRendering() const
{
    return testOption(QWindowFormat::DirectRendering);
}

inline bool QWindowFormat::hasWindowSurface() const
{
    return testOption(QWindowFormat::HasWindowSurface);
}

inline bool QWindowFormat::sampleBuffers() const
{
    return testOption(QWindowFormat::SampleBuffers);
}

QT_END_NAMESPACE

QT_END_HEADER

#endif //QPLATFORMWINDOWFORMAT_QPA_H
