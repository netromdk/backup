#include "util/Paths.h"
#include "ServerConfig.h"
#include "config/Config.h"

ServerConfig::ServerConfig() : tree(NULL) {
  path = Paths::getConfigDir();
}

ServerConfig::~ServerConfig() {
  if (tree) {
    delete tree;
  }
}

void ServerConfig::print(QDebug dbg) const {
  dbg << "ServerConfig @" << path << "=";
  if (tree) {
    tree->print(dbg);
  }
}
