// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "qwaylandcompositorextension.h"
#include "qwaylandcompositorextension_p.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

#include <wayland-server-core.h>

QT_BEGIN_NAMESPACE

/*!
 * \class QWaylandCompositorExtensionTemplate
 * \inmodule QtWaylandCompositor
 * \since 5.8
 * \brief QWaylandCompositorExtensionTemplate is a convenience class for subclassing
 * QWaylandCompositorExtension.
 *
 * QWaylandCompositorExtensionTemplate is a template class which inherits
 * QWaylandCompositorExtension and is convenience for building custom Wayland extensions with Qt.
 *
 * It provides the connection between Qt Wayland Compositor and the class generated by
 * \c qtwaylandscanner, based on the XML description of the extension protocol.
 *
 * It provides two specific pieces of convenience:
 * \list
 *   \li A reimplementation of \l{QWaylandCompositorExtension::extensionInterface()} which returns
 *   the \c wl_interface pointer for the qtwaylandscanner-generated base class.
 *   \li A static \l{findIn()} function which searches for an instance of the extension in a
 *   provided container, and returns this if it is found.
 * \endlist
 *
 * Typically, a new extension will dual-inherit QWaylandCompositorExtensionTemplate and the class
 * generated by \c qtwaylandscanner.
 *
 * QWaylandCompositorExtensionTemplate should be parameterized with the subclass itself:
 * \code
 * class MyExtension
 *     : public QWaylandCompositorExtensionTemplate<MyExtension>
 *     , QtWaylandServer::my_extension
 * \endcode
 *
 * In this example, \c MyExtension is an implementation of the generated interface \c my_extension.
 *
 * \sa {Qt Wayland Compositor Examples - Custom Shell}
 */

/*!
 *  \fn template <typename T> T *QWaylandCompositorExtensionTemplate<T>::findIn(QWaylandObject *container)
 *
 *  If any instance of the interface has been registered with \a container, this is returned.
 *  Otherwise null is returned. The look-up is based on the generated \c interfaceName() which
 *  matches the interface name in the protocol description.
 */

/*!
 * \class QWaylandCompositorExtension
 * \inmodule QtWaylandCompositor
 * \since 5.8
 * \brief QWaylandCompositorExtension is the base class for compositor extensions.
 *
 * QWaylandCompositorExtension is the base class for implementing Wayland extensions on the
 * compositor-side of the connection. If no other extension container is explicitly set, it will
 * automatically add itself to its parent object, granted that this inherits from QWaylandObject.
 *
 * For example, for registering global extensions, you can inherit from QWaylandCompositorExtension
 * and pass the QWaylandCompositor object as extension container.
 *
 * \sa QWaylandCompositorExtensionTemplate, {Qt Wayland Compositor Examples - Custom Shell}
 */

/*!
 * Creates a QWaylandCompositorExtension with no container.
 *
 * \sa setExtensionContainer()
 */
QWaylandCompositorExtension::QWaylandCompositorExtension()
    : QWaylandObject(*new QWaylandCompositorExtensionPrivate())
{
}

/*!
 * Creates a QWaylandCompositorExtension and adds it to the extension \a container. The \a container
 * does not become the parent of the QWaylandCompositorExtension.
 *
 * The extension adds itself to \a container later, when \l{initialize()} is called. For this to
 * happen automatically, an event loop must be running in the current thread.
 *
 * The QWaylandCompositorExtension will remove itself again when it is destroyed.
 */
QWaylandCompositorExtension::QWaylandCompositorExtension(QWaylandObject *container)
    : QWaylandObject(*new QWaylandCompositorExtensionPrivate())
{
    d_func()->extension_container = container;
    QCoreApplication::postEvent(this, new QEvent(QEvent::Polish));
}

QWaylandCompositorExtension::QWaylandCompositorExtension(QWaylandCompositorExtensionPrivate &dd)
    : QWaylandObject(dd)
{
}

QWaylandCompositorExtension::QWaylandCompositorExtension(QWaylandObject *container, QWaylandCompositorExtensionPrivate &dd)
    : QWaylandObject(dd)
{
    d_func()->extension_container = container;
    QCoreApplication::postEvent(this, new QEvent(QEvent::Polish));
}

QWaylandCompositorExtension::~QWaylandCompositorExtension()
{
    Q_D(QWaylandCompositorExtension);
    if (d->extension_container)
        d->extension_container->removeExtension(this);
}

/*!
 *  \fn const wl_interface *QWaylandCompositorExtension::extensionInterface() const
 *
 *  A pure virtual function which should be reimplemented to return the \c wl_interface which
 *  corresponds to this QWaylandCompositorExtension.
 */

/*!
 * \return the extension container for this QWaylandCompositorExtension or null if none has been
 * set.
 */
QWaylandObject *QWaylandCompositorExtension::extensionContainer() const
{
    Q_D(const QWaylandCompositorExtension);
    return d->extension_container;
}

/*!
 * Sets the extension container for this QWaylandCompositorExtension to \a container. This must be
 * called before \l{initialize()} and cannot be changed once the QWaylandCompositorExtension has
 * been initialized.
 */
void QWaylandCompositorExtension::setExtensionContainer(QWaylandObject *container)
{
    Q_D(QWaylandCompositorExtension);
    d->extension_container = container;
}

/*!
 * Initializes the QWaylandCompositorExtension. The default implementation adopts the parent object
 * as extension container if none has been set, and if the parent inherits from QWaylandObject. The
 * default implementation also adds the QWaylandCompositorExtension to the list of extensions
 * managed by the extension container.
 *
 * Override this function in subclasses to provide custom initialization code.
 */
void QWaylandCompositorExtension::initialize()
{
    Q_D(QWaylandCompositorExtension);
    if (d->initialized) {
        qWarning() << "QWaylandCompositorExtension:" << extensionInterface()->name << "is already initialized";
        return;
    }

    if (!d->extension_container && parent()) {
        QWaylandObject *parentObj = qobject_cast<QWaylandObject*>(parent());
        if (parentObj)
            setExtensionContainer(parentObj);
    }

    if (!d->extension_container) {
        qWarning() << "QWaylandCompositorExtension:" << extensionInterface()->name << "requests to initialize with no extension container set";
        return;
    }

    d->extension_container->addExtension(this);
    d->initialized = true;
}

bool QWaylandCompositorExtension::isInitialized() const
{
    Q_D(const QWaylandCompositorExtension);
    return d->initialized;
}

bool QWaylandCompositorExtension::event(QEvent *event)
{
    switch(event->type()) {
    case QEvent::Polish:
        if (!isInitialized())
            initialize();
        break;
    default:
        break;
    }
    return QWaylandObject::event(event);
}

/*!
 * \class QWaylandObject
 * \inmodule QtWaylandCompositor
 * \since 5.8
 * \brief QWaylandObject is the base class for objects that can contain Wayland extensions.
 *
 * The QWaylandObject encapsulate extension container functionality. Any QWaylandObject object
 * will automatically be an extension container and QWaylandCompositorExtension object which is
 * a child of this will automatically add itself to its extension list, and remove itself when
 * the extension object is destroyed.
 */

/*!
 *  Creates a QWaylandObject as a child of \a parent.
 */
QWaylandObject::QWaylandObject(QObject *parent)
    :QObject(parent)
{
}

QWaylandObject::QWaylandObject(QObjectPrivate &d, QObject *parent)
    :QObject(d, parent)
{
}


QWaylandObject::~QWaylandObject()
{
    for (QWaylandCompositorExtension *extension : qAsConst(extension_vector))
        QWaylandCompositorExtensionPrivate::get(extension)->extension_container = nullptr;
}

/*!
 *  Returns the compositor extension which matches \a name if one has been registered with the
 *  QWaylandObject. If no extension matching the name has been registered, this function returns
 *  null.
 */
QWaylandCompositorExtension *QWaylandObject::extension(const QByteArray &name)
{
    for (int i = 0; i < extension_vector.size(); i++) {
        if (extension_vector.at(i)->extensionInterface()->name == name)
            return extension_vector.at(i);
    }
    return nullptr;
}

/*!
 *  Returns the compositor extension which matches \a interface if one has been registered with the
 *  QWaylandObject. If no extension matching the interface has been registered, this function
 *  returns null.
 */
QWaylandCompositorExtension *QWaylandObject::extension(const wl_interface *interface)
{
    for (int i = 0; i < extension_vector.size(); i++) {
        if (extension_vector.at(i)->extensionInterface() == interface)
            return extension_vector.at(i);
    }
    return nullptr;
}

/*!
 *  Returns the list of compositor extensions that have been registered with this QWaylandObject.
 */
QList<QWaylandCompositorExtension *> QWaylandObject::extensions() const
{
    return extension_vector;
}

/*!
 *  Registers \a extension with this QWaylandObject.
 */
void QWaylandObject::addExtension(QWaylandCompositorExtension *extension)
{
    Q_ASSERT(!extension_vector.contains(extension));
    extension_vector.append(extension);
}

/*!
 *  Removes \a extension from the list of registered extensions in this QWaylandObject, if it has
 *  previously been registered using \l{addExtension()}.
 */
void QWaylandObject::removeExtension(QWaylandCompositorExtension *extension)
{
    Q_ASSERT(extension_vector.contains(extension));
    extension_vector.removeOne(extension);
}

QT_END_NAMESPACE

#include "moc_qwaylandcompositorextension.cpp"
