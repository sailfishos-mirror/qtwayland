// Copyright (C) 2016 Jolla Ltd
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#include "qwaylandshellintegrationplugin_p.h"

QT_BEGIN_NAMESPACE

namespace QtWaylandClient {

QWaylandShellIntegrationPlugin::QWaylandShellIntegrationPlugin(QObject *parent)
                              : QObject(parent)
{
}

QWaylandShellIntegrationPlugin::~QWaylandShellIntegrationPlugin()
{
}

}

QT_END_NAMESPACE

#include "moc_qwaylandshellintegrationplugin_p.cpp"
