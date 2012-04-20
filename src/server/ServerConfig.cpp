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

bool ServerConfig::save() {
  if (!tree) return false;
  return config.commit(tree);
}

void ServerConfig::print(QDebug dbg) const {
  if (tree) {
    tree->print(dbg);
  }
}

void ServerConfig::load() {
  tree = config.parse();
  valid = tree;

  if (config.getErrors().testFlag(Config::PathNonExistent)) {
    qDebug() << "Config does not exist:" << config.getPath();
    qDebug() << "Writing default.";
    writeDefault();
    load();
    return;
  }
  
  if (!valid) {
    qCritical() << "Could not load/parse config file:" << config.getPath();
    return;
  }
  
  valid = true;

  // TODO: Check that the types are correct and required fields exist.

  // Set the values for type-safe retrieval.
  portVar =
    tree->searchNode("ServerConfig/Port")->getValues()[0].toString().toUInt();
}

void ServerConfig::writeDefault() {

  /// TODO:
  //    Add DefaultConfig class with:
  //      enum DefaultItemName { Port, .. };
  //      struct DefaultItem { ..value, ..comment };
  //      static ConfigTreeNode *create()
  //      static DefaultItem getDefaultValue(DefaultItemName item);
  
  if (tree) delete tree;

  tree = new ConfigTreeNode("root");

  ConfigTreeNode *serverConfig = new ConfigTreeNode("ServerConfig");
  tree->addNode(serverConfig);

  ConfigTreeNode *port = new ConfigTreeNode("Port");
  port->addValue(4512);
  port->setComment("The port the server should bind to.");
  serverConfig->addNode(port);

  save();
}
