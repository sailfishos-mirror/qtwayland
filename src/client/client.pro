TARGET = QtWaylandClient
MODULE = waylandclient

QT += core-private gui-private
QT_FOR_PRIVATE += service_support-private
QT_PRIVATE += fontdatabase_support-private eventdispatcher_support-private theme_support-private

# We have a bunch of C code with casts, so we can't have this option
QMAKE_CXXFLAGS_WARN_ON -= -Wcast-qual

# Prevent gold linker from crashing.
# This started happening when QtPlatformSupport was modularized.
use_gold_linker: CONFIG += no_linker_version_script

CONFIG -= precompile_header
CONFIG += link_pkgconfig wayland-scanner

contains(QT_CONFIG, opengl) {
    DEFINES += QT_WAYLAND_GL_SUPPORT
}

config_xkbcommon {
    !contains(QT_CONFIG, no-pkg-config) {
        PKGCONFIG_PRIVATE += xkbcommon
    } else {
        LIBS_PRIVATE += -lxkbcommon
    }
} else {
    DEFINES += QT_NO_WAYLAND_XKB
}

!contains(QT_CONFIG, no-pkg-config) {
    PKGCONFIG_PRIVATE += wayland-client wayland-cursor
    contains(QT_CONFIG, glib): PKGCONFIG_PRIVATE += glib-2.0
} else {
    LIBS_PRIVATE += -lwayland-client -lwayland-cursor $$QT_LIBS_GLIB
}

INCLUDEPATH += $$PWD/../shared

WAYLANDCLIENTSOURCES += \
            ../3rdparty/protocol/wayland.xml \
            ../extensions/surface-extension.xml \
            ../extensions/touch-extension.xml \
            ../extensions/qtkey-extension.xml \
            ../extensions/qt-windowmanager.xml \
            ../3rdparty/protocol/text-input-unstable-v2.xml \
            ../3rdparty/protocol/xdg-shell.xml \

SOURCES +=  qwaylandintegration.cpp \
            qwaylandnativeinterface.cpp \
            qwaylandshmbackingstore.cpp \
            qwaylandinputdevice.cpp \
            qwaylandcursor.cpp \
            qwaylanddisplay.cpp \
            qwaylandwindow.cpp \
            qwaylandscreen.cpp \
            qwaylandshmwindow.cpp \
            qwaylandclipboard.cpp \
            qwaylanddnd.cpp \
            qwaylanddataoffer.cpp \
            qwaylanddatadevicemanager.cpp \
            qwaylanddatasource.cpp \
            qwaylandshellsurface.cpp \
            qwaylandwlshellsurface.cpp \
            qwaylandwlshellintegration.cpp \
            qwaylandxdgshell.cpp \
            qwaylandxdgsurface.cpp \
            qwaylandxdgpopup_p.cpp \
            qwaylandxdgshellintegration.cpp \
            qwaylandextendedsurface.cpp \
            qwaylandsubsurface.cpp \
            qwaylandtouch.cpp \
            qwaylandqtkey.cpp \
            ../shared/qwaylandmimehelper.cpp \
            ../shared/qwaylandxkb.cpp \
            ../shared/qwaylandinputmethodeventbuilder.cpp \
            qwaylandabstractdecoration.cpp \
            qwaylanddecorationfactory.cpp \
            qwaylanddecorationplugin.cpp \
            qwaylandwindowmanagerintegration.cpp \
            qwaylandinputcontext.cpp \
            qwaylanddatadevice.cpp \
            qwaylandshm.cpp \
            qwaylandbuffer.cpp \

HEADERS +=  qwaylandintegration_p.h \
            qwaylandnativeinterface_p.h \
            qwaylandcursor_p.h \
            qwaylanddisplay_p.h \
            qwaylandwindow_p.h \
            qwaylandscreen_p.h \
            qwaylandshmbackingstore_p.h \
            qwaylandinputdevice_p.h \
            qwaylandbuffer_p.h \
            qwaylandshmwindow_p.h \
            qwaylandclipboard_p.h \
            qwaylanddnd_p.h \
            qwaylanddataoffer_p.h \
            qwaylanddatadevicemanager_p.h \
            qwaylanddatasource_p.h \
            qwaylandshellsurface_p.h \
            qwaylandwlshellsurface_p.h \
            qwaylandwlshellintegration_p.h \
            qwaylandxdgshell_p.h \
            qwaylandxdgsurface_p.h \
            qwaylandxdgpopup_p.h \
            qwaylandxdgshellintegration_p.h \
            qwaylandextendedsurface_p.h \
            qwaylandsubsurface_p.h \
            qwaylandtouch_p.h \
            qwaylandqtkey_p.h \
            qwaylandabstractdecoration_p.h \
            qwaylanddecorationfactory_p.h \
            qwaylanddecorationplugin_p.h \
            qwaylandwindowmanagerintegration_p.h \
            qwaylandinputcontext_p.h \
            qwaylanddatadevice_p.h \
            qwaylandshm_p.h \
            qwaylandclientexport.h \
            ../shared/qwaylandinputmethodeventbuilder_p.h \
            ../shared/qwaylandmimehelper_p.h \
            ../shared/qwaylandxkb_p.h \
            ../shared/qwaylandsharedmemoryformathelper_p.h

include(hardwareintegration/hardwareintegration.pri)
include(shellintegration/shellintegration.pri)
include(inputdeviceintegration/inputdeviceintegration.pri)
include(global/global.pri)

CONFIG += generated_privates
MODULE_PLUGIN_TYPES = \
            wayland-graphics-integration-client \
            wayland-inputdevice-integration \
            wayland-decoration-client \
            wayland-shell-integration
load(qt_module)
