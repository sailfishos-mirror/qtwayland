/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the Qt Compositor.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef GRAPHICSHARDWAREINTEGRATION_H
#define GRAPHICSHARDWAREINTEGRATION_H

#include <QtGui/qopengl.h>
#include <QtGui/QOpenGLContext>
#include <wayland-server.h>

#include "waylandcompositor.h"
#include "wayland_wrapper/wldisplay.h"

class GraphicsHardwareIntegration
{
public:
    GraphicsHardwareIntegration(WaylandCompositor *compositor);
    virtual ~GraphicsHardwareIntegration() { }

    virtual void initializeHardware(Wayland::Display *waylandDisplay) = 0;

    /** Bind the Wayland buffer to the textureId. The correct context is the current context,
        so there is no need to do makeCurrent in this function.
     **/
    virtual GLuint createTextureFromBuffer(struct wl_buffer *buffer, QOpenGLContext *context) = 0;
    virtual bool isYInverted(struct wl_buffer *) const { return true; }

    virtual bool setDirectRenderSurface(WaylandSurface *) {return false;}

    virtual void *toNativeBufferHandle(struct wl_buffer *) { return 0; }

    static GraphicsHardwareIntegration *createGraphicsHardwareIntegration(WaylandCompositor *compositor);

protected:
    WaylandCompositor *m_compositor;
};

#endif // GRAPHICSHARDWAREINTEGRATION_H
