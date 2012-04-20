#include "DefaultConfig.h"
#include "config/Config.h"

ConfigTreeNode *DefaultConfig::create() {
  ConfigTreeNode *tree = new ConfigTreeNode("root");

  ConfigTreeNode *serverConfig = new ConfigTreeNode("ServerConfig");
  tree->addNode(serverConfig);

  DefaultConfigItem item = getDefault(Port);
  ConfigTreeNode *port = new ConfigTreeNode("Port");
  port->addValue(item.value);
  port->setComment(item.comment);
  serverConfig->addNode(port);

  return tree;
}

DefaultConfigItem DefaultConfig::getDefault(DefaultConfigItemName name) {
  DefaultConfigItem item;

  switch (name) {
  case Port:
    item.value = 4512;
    item.comment = "The port the server should bind to.";
    break;
  }

  return item;
}
