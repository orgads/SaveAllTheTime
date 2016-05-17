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
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>
#include <QTimer>

#define ONE_SECOND_MILLIS 1000

namespace SaveAllTheTime {
  namespace Internal {

    SaveAllTheTimePlugin::SaveAllTheTimePlugin() :
      m_action( nullptr ),
      m_settings( new Settings )
    {
      m_settings->fromSettings( Core::ICore::settings() );
      SettingsPage* settingsPage = new SettingsPage( m_settings );
      addAutoReleasedObject( settingsPage );
      connect( settingsPage, & SettingsPage::applied,
               this,         & SaveAllTheTimePlugin::refreshTimer );

      m_timer = new QTimer( this );
      connect( m_timer, SIGNAL( timeout() ),
               this,    SLOT( saveAll() ) );
      refreshTimer();
      m_timer->start();
    }

    SaveAllTheTimePlugin::~SaveAllTheTimePlugin()
    {
      // Unregister objects from the plugin manager's object pool
      // Delete members
    }

    bool SaveAllTheTimePlugin::initialize(const QStringList &arguments, QString *errorString)
    {
      // Register objects in the plugin manager's object pool
      // Load settings
      // Add actions to menus
      // Connect to other plugins' signals
      // In the initialize function, a plugin can be sure that the plugins it
      // depends on have initialized their members.

      Q_UNUSED(arguments)
      Q_UNUSED(errorString)

      QAction *action = new QAction(tr("Save All The Time"), this);
      m_action = action;
      Core::Command *cmd = Core::ActionManager::registerAction(action, Constants::ACTION_ID,
                                                               Core::Context(Core::Constants::C_GLOBAL));
      cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+S")));
      connect(action, SIGNAL(triggered()), this, SLOT(triggerAction()));
      Core::ActionContainer *menu = Core::ActionManager::actionContainer(Core::Constants::M_TOOLS);
      menu->addAction(cmd);

      action->setCheckable( true );
      action->setChecked( true );

      return true;
    }

    void SaveAllTheTimePlugin::extensionsInitialized()
    {
      // Retrieve objects from the plugin manager's object pool
      // In the extensionsInitialized function, a plugin can be sure that all
      // plugins that depend on it are completely initialized.
    }

    ExtensionSystem::IPlugin::ShutdownFlag SaveAllTheTimePlugin::aboutToShutdown()
    {
      // Save settings
      // Disconnect from signals that are not needed during shutdown
      // Hide UI (if you add UI that is not in the main window directly)
      return SynchronousShutdown;
    }

    void SaveAllTheTimePlugin::saveAll()
    {
      Core::DocumentManager::saveAllModifiedDocumentsSilently();
    }

    int SaveAllTheTimePlugin::getInterval()
    {
      return m_settings->interval * ONE_SECOND_MILLIS;
    }

    void SaveAllTheTimePlugin::refreshTimer()
    {
      const bool isActive = m_timer->isActive();
      if ( isActive )
      {
        m_timer->stop();
      }

      m_timer->setInterval( getInterval() );

      if ( isActive )
      {
        m_timer->start();
      }
    }

    void SaveAllTheTimePlugin::triggerAction()
    {
      if ( m_action && m_action->isChecked() )
      {
        m_timer->start( getInterval() );
      }
      else
      {
        m_timer->stop();
      }
    }

  } // namespace Internal
} // namespace SaveAllTheTime
