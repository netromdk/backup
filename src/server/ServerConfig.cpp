#include "ServerConfig.h"
#include "util/Paths.h"

ServerConfig::ServerConfig() : tree(NULL) {
  path = Paths::getConfigDir();
}

ServerConfig::~ServerConfig() {
  if (tree) {
    delete tree;
  }
}

