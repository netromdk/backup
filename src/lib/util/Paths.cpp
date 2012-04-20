#include <QDir>

#include "Paths.h"

QString Paths::configDir = "";

QString Paths::getConfigDir() {
  if (!configDir.isEmpty()) {
    return configDir;
  }

  // TODO:
  // Have a look at the paths Qt uses for QSettings.

#ifdef __APPLE__
  configDir = QDir::homePath() + "/Library/Application Support/backup/";
#endif
  
  return configDir;
}
