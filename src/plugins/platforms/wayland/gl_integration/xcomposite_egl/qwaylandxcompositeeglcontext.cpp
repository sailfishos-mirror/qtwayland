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

#include "qwaylandxcompositeeglcontext.h"

#include "qwaylandxcompositeeglwindow.h"

#include <QtCore/QDebug>
#include <QtGui/QRegion>

#include <QtPlatformSupport/private/qeglconvenience_p.h>

QWaylandXCompositeEGLContext::QWaylandXCompositeEGLContext(const QSurfaceFormat &format, QPlatformOpenGLContext *share, EGLDisplay display)
    : QEGLPlatformContext(format, share, display)
{
}

void QWaylandXCompositeEGLContext::swapBuffers(QPlatformSurface *surface)
{
    QEGLPlatformContext::swapBuffers(surface);

    QWaylandXCompositeEGLWindow *w =
        static_cast<QWaylandXCompositeEGLWindow *>(surface);

    QSize size = w->geometry().size();

    w->damage(QRect(QPoint(), size));
    w->waitForFrameSync();
}

EGLSurface QWaylandXCompositeEGLContext::eglSurfaceForPlatformSurface(QPlatformSurface *surface)
{
    return static_cast<QWaylandXCompositeEGLWindow *>(surface)->eglSurface();
}
