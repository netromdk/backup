#include <QDir>

#include "Env.h"
#include "Paths.h"

QString Paths::configDir = "";

QString Paths::getConfigDir() {
  if (!configDir.isEmpty()) {
    return configDir;
  }

#ifdef WIN
  configDir = Env::get("%APPDATA%", QDir::tempPath()) + "/backup";
#elif UNIX
  configDir = QDir::homePath() + "/.backup";
#endif
  
  return configDir;
}
