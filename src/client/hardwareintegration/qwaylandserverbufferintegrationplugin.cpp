// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#include "qwaylandserverbufferintegrationplugin_p.h"

QT_BEGIN_NAMESPACE

namespace QtWaylandClient {

QWaylandServerBufferIntegrationPlugin::QWaylandServerBufferIntegrationPlugin(QObject *parent)
    : QObject(parent)
{
}
QWaylandServerBufferIntegrationPlugin::~QWaylandServerBufferIntegrationPlugin()
{
}

}

QT_END_NAMESPACE

#include "moc_qwaylandserverbufferintegrationplugin_p.cpp"
