// Copyright (C) 2016 Robin Burchell <robin.burchell@viroteck.net>
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#include "qwaylanddecorationplugin_p.h"

QT_BEGIN_NAMESPACE

namespace QtWaylandClient {

QWaylandDecorationPlugin::QWaylandDecorationPlugin(QObject *parent)
    : QObject(parent)
{
}
QWaylandDecorationPlugin::~QWaylandDecorationPlugin()
{
}

}

QT_END_NAMESPACE

#include "moc_qwaylanddecorationplugin_p.cpp"
