//Public Domain License

#pragma once

#include "saveallthetime_global.h"
#include "settings.h"
#include <extensionsystem/iplugin.h>

#include <QSharedPointer>

QT_BEGIN_NAMESPACE
class QAction;
class QTimer;
QT_END_NAMESPACE

namespace SaveAllTheTime {
namespace Internal {

class SaveAllTheTimePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "SaveAllTheTime.json")

public:
    SaveAllTheTimePlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();

private:
    void refreshTimer();
    void triggerAction();

private:
    int getInterval();

    QAction *m_action = nullptr;
    QTimer *m_timer = nullptr;
    const QSharedPointer<Settings> m_settings;
    int m_seconds = 0;
};

} // namespace Internal
} // namespace SaveAllTheTime
