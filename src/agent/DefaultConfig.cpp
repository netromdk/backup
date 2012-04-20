#include "DefaultConfig.h"
#include "config/Config.h"

ConfigTreeNode *DefaultConfig::create() {
  ConfigTreeNode *tree = new ConfigTreeNode("root");

  ConfigTreeNode *agentConfig = new ConfigTreeNode("AgentConfig");
  tree->addNode(agentConfig);

  DefaultConfigItem item = getDefault(Host);
  ConfigTreeNode *host = new ConfigTreeNode("Host");
  host->addValue(item.value);
  host->setComment(item.comment);
  agentConfig->addNode(host);    

  item = getDefault(Port);
  ConfigTreeNode *port = new ConfigTreeNode("Port");
  port->addValue(item.value);
  port->setComment(item.comment);
  agentConfig->addNode(port);

  return tree;
}

DefaultConfigItem DefaultConfig::getDefault(DefaultConfigItemName name) {
  DefaultConfigItem item;

  switch (name) {
  case Host:
    item.value = "127.0.0.1";
    item.comment = "The host name the agent should connect to.";
    break;

  case Port:
    item.value = 4512;
    item.comment = "The remote port the agent should bind to.";
    break;    
  }

  return item;
}
