//Public Domain License

#pragma once

#include "saveallthetime_global.h"
#include "settings.h"
#include <extensionsystem/iplugin.h>

#include <QSharedPointer>

class QAction;
class QTimer;

namespace SaveAllTheTime {
  namespace Internal {

    class SaveAllTheTimePlugin : public ExtensionSystem::IPlugin
    {
      Q_OBJECT
      Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "SaveAllTheTime.json")

    public:
      SaveAllTheTimePlugin();
      ~SaveAllTheTimePlugin();

      bool initialize(const QStringList &arguments, QString *errorString);
      void extensionsInitialized();
      ShutdownFlag aboutToShutdown();


    private slots:
      void refreshTimer();
      void saveAll();
      void triggerAction();

    private:
      int getInterval();

      QAction* m_action;
      int      m_seconds;
      const QSharedPointer<Settings> m_settings;
      QTimer*  m_timer;
    };

  } // namespace Internal
} // namespace SaveAllTheTime
