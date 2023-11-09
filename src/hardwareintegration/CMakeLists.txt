# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial

if(TARGET Qt::WaylandClient)
    add_subdirectory(client)
endif()
if(TARGET Qt::WaylandCompositor)
    add_subdirectory(compositor)
endif()
