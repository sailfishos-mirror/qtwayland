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

#include "wlextendedoutput.h"

#include "wlcompositor.h"
#include "wloutput.h"

namespace Wayland {

OutputExtensionGlobal::OutputExtensionGlobal(Compositor *compositor)
    : m_compositor(compositor)
{
    wl_display_add_global(compositor->wl_display(),
                          &wl_output_extension_interface,
                          this,
                          OutputExtensionGlobal::bind_func);
}

void OutputExtensionGlobal::bind_func(wl_client *client, void *data, uint32_t version, uint32_t id)
{
    Q_UNUSED(version);
    wl_client_add_object(client,&wl_output_extension_interface,&output_extension_interface,id,data);
}

void OutputExtensionGlobal::get_extended_output(wl_client *client, wl_resource *output_extension_resource, uint32_t id, wl_resource *output_resource)
{
    OutputExtensionGlobal *output_extension = static_cast<OutputExtensionGlobal *>(output_extension_resource->data);
    Output *output = static_cast<Output *>(output_resource->data);
    new ExtendedOutput(client,id,output,output_extension->m_compositor);
}

const struct wl_output_extension_interface OutputExtensionGlobal::output_extension_interface = {
    OutputExtensionGlobal::get_extended_output
};

ExtendedOutput::ExtendedOutput(struct wl_client *client, uint32_t id, Output *output, Compositor *compositor)
    : m_output(output)
    , m_compositor(compositor)
{
    Q_ASSERT(m_output->extendedOutput() == 0);
    m_output->setExtendedOutput(this);
    m_extended_output_resource = wl_client_add_object(client,&wl_extended_output_interface,0,id,this);
    sendOutputOrientation(m_compositor->screenOrientation());
}

void ExtendedOutput::sendOutputOrientation(Qt::ScreenOrientation orientation)
{
    int sendOpperation;
    switch (orientation) {
        case Qt::PortraitOrientation:
            sendOpperation = WL_EXTENDED_OUTPUT_ROTATION_PORTRAITORIENTATION;
            break;
    case Qt::LandscapeOrientation:
            sendOpperation = WL_EXTENDED_OUTPUT_ROTATION_LANDSCAPEORIENTATION;
            break;
    case Qt::InvertedPortraitOrientation:
            sendOpperation = WL_EXTENDED_OUTPUT_ROTATION_INVERTEDPORTRAITORIENTATION;
            break;
    case Qt::InvertedLandscapeOrientation:
            sendOpperation = WL_EXTENDED_OUTPUT_ROTATION_INVERTEDLANDSCAPEORIENTATION;
            break;
    default:
        sendOpperation = WL_EXTENDED_OUTPUT_ROTATION_PORTRAITORIENTATION;
    }
    wl_resource_post_event(m_extended_output_resource,WL_EXTENDED_OUTPUT_SET_SCREEN_ROTATION,sendOpperation);
}


}
