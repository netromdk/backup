#include "Paths.h"

QString Paths::configDir = "";

QString Paths::getConfigDir() {
  if (!configDir.isEmpty()) {
    return configDir;
  }

  // TODO:
  // Have a look at the paths Qt uses for QSettings.
  
  configDir = "~/test.conf";
  
  return configDir;
}
