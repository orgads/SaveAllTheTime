#pragma once

#include "saveallthetime_global.h"

#include <extensionsystem/iplugin.h>

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
      void triggerAction();
    };

  } // namespace Internal
} // namespace SaveAllTheTime
