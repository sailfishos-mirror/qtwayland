/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWAYLANDXCOMPOSITEGLXWINDOW_H
#define QWAYLANDXCOMPOSITEGLXWINDOW_H

#include "qwaylandwindow.h"
#include "qwaylandxcompositeglxintegration.h"
#include "qwaylandxcompositeglxcontext.h"

#include <QtCore/QWaitCondition>

#include "qwaylandbuffer.h"

class QWaylandXCompositeGLXWindow : public QWaylandWindow
{
public:
    QWaylandXCompositeGLXWindow(QWindow *window, QWaylandXCompositeGLXIntegration *glxIntegration);
    WindowType windowType() const;

    void setGeometry(const QRect &rect);

    Window xWindow() const;

private:
    void createSurface();

    QWaylandXCompositeGLXIntegration *m_glxIntegration;

    Window m_xWindow;
    GLXFBConfig m_config;

    QWaylandBuffer *m_buffer;

    void waitForSync();
    bool m_waitingForSync;

    static const struct wl_callback_listener sync_callback_listener;
    static void sync_function(void *data, struct wl_callback *wl_callback, uint32_t time);
};

#endif // QWAYLANDXCOMPOSITEGLXWINDOW_H
