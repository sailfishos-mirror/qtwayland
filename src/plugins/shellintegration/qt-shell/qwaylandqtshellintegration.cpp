// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#include "qwaylandqtshellintegration.h"

#include <QtCore/qsize.h>
#include <QtCore/qdebug.h>

#include <QtWaylandClient/private/qwaylanddisplay_p.h>
#include <QtWaylandClient/private/qwaylandwindow_p.h>

#include "qwaylandqtsurface_p.h"

#include <mutex>

#include <unistd.h>

QT_BEGIN_NAMESPACE

namespace QtWaylandClient {

QWaylandQtShellIntegration::QWaylandQtShellIntegration()
    : QWaylandShellIntegrationTemplate(1)
{
    QWaylandWindow::fixedToplevelPositions = false;
}

QWaylandShellSurface *QWaylandQtShellIntegration::createShellSurface(QWaylandWindow *window)
{
    auto *surface = surface_create(wlSurfaceForWindow(window));
    return new QWaylandQtSurface(surface, window);
}

}

QT_END_NAMESPACE
