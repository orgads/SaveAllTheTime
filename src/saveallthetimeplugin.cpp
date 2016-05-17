//Public Domain License

#include "saveallthetimeplugin.h"
#include "saveallthetimeconstants.h"
#include "settings.h"
#include "settingspage.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/documentmanager.h>

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QTimer>

#define ONE_SECOND_MILLIS 1000

namespace SaveAllTheTime {
namespace Internal {

SaveAllTheTimePlugin::SaveAllTheTimePlugin() :
    m_settings(new Settings)
{
    m_settings->fromSettings(Core::ICore::settings());
    SettingsPage* settingsPage = new SettingsPage(m_settings);
    addAutoReleasedObject(settingsPage);
    connect(settingsPage, &SettingsPage::applied,
            this, &SaveAllTheTimePlugin::refreshTimer);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout,
            this, []() { Core::DocumentManager::saveAllModifiedDocumentsSilently(); });
    refreshTimer();
    m_timer->start();
}

bool SaveAllTheTimePlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    m_action = new QAction(tr("Save All The Time"), this);
    Core::Command *cmd = Core::ActionManager::registerAction(m_action, Constants::ACTION_ID,
                                                             Core::Context(Core::Constants::C_GLOBAL));
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+S")));
    connect(m_action, &QAction::triggered, this, &SaveAllTheTimePlugin::triggerAction);
    Core::ActionContainer *menu = Core::ActionManager::actionContainer(Core::Constants::M_TOOLS);
    menu->addAction(cmd);

    m_action->setCheckable(true);
    m_action->setChecked(true);

    return true;
}

void SaveAllTheTimePlugin::extensionsInitialized()
{
}

int SaveAllTheTimePlugin::getInterval()
{
    return m_settings->interval * ONE_SECOND_MILLIS;
}

void SaveAllTheTimePlugin::refreshTimer()
{
    const bool isActive = m_timer->isActive();
    if (isActive)
        m_timer->stop();

    m_timer->setInterval(getInterval());

    if (isActive)
        m_timer->start();
}

void SaveAllTheTimePlugin::triggerAction()
{
    if (m_action && m_action->isChecked())
        m_timer->start(getInterval());
    else
        m_timer->stop();
}

} // namespace Internal
} // namespace SaveAllTheTime
