// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#include "qwaylandshmwindow_p.h"

#include "qwaylandbuffer_p.h"

#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

namespace QtWaylandClient {

QWaylandShmWindow::QWaylandShmWindow(QWindow *window, QWaylandDisplay *display)
    : QWaylandWindow(window, display)
{
}

QWaylandShmWindow::~QWaylandShmWindow()
{
}

QWaylandWindow::WindowType QWaylandShmWindow::windowType() const
{
    return QWaylandWindow::Shm;
}

}

QT_END_NAMESPACE
