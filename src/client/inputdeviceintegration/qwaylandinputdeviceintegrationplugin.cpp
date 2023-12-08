// Copyright (C) 2016 LG Electronics Ltd
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#include "qwaylandinputdeviceintegrationplugin_p.h"

QT_BEGIN_NAMESPACE

namespace QtWaylandClient {

QWaylandInputDeviceIntegrationPlugin::QWaylandInputDeviceIntegrationPlugin(QObject *parent)
                              : QObject(parent)
{
}

QWaylandInputDeviceIntegrationPlugin::~QWaylandInputDeviceIntegrationPlugin()
{
}

}

QT_END_NAMESPACE

#include "moc_qwaylandinputdeviceintegrationplugin_p.cpp"
