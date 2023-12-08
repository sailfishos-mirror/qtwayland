// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#include "qwaylandclientbufferintegrationplugin_p.h"

QT_BEGIN_NAMESPACE

namespace QtWaylandClient {

QWaylandClientBufferIntegrationPlugin::QWaylandClientBufferIntegrationPlugin(QObject *parent) :
    QObject(parent)
{
}

QWaylandClientBufferIntegrationPlugin::~QWaylandClientBufferIntegrationPlugin()
{
}

}

QT_END_NAMESPACE

#include "moc_qwaylandclientbufferintegrationplugin_p.cpp"
