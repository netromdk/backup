#include "util/Paths.h"
#include "ServerConfig.h"

ServerConfig::ServerConfig() : tree(NULL), valid(false) {
  config.setPath(Paths::getConfigDir() + "/srv.conf");  
  load();
}

ServerConfig::~ServerConfig() {
  if (tree) {
    delete tree;
  }
}

void ServerConfig::load() {
  tree = config.parse();
  valid = tree;

  if (config.getErrors().testFlag(Config::PathNonExistent)) {
    qDebug() << "Config does not exist:" << config.getPath();
    // TODO:
    //  Write default.
    //  load();
    return;
  }
  
  if (!valid) {
    qCritical() << "Could not load/parse config file:" << config.getPath();
    return;
  }
  
  valid = true;
}
               
bool ServerConfig::save() {
  if (!tree) return false;
  return config.commit(tree);
}

void ServerConfig::print(QDebug dbg) const {
  dbg.nospace() << "ServerConfig @ " << config.getPath() << " =\n";
  if (tree) {
    tree->print(dbg);
  }
}
