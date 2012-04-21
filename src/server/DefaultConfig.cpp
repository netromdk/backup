#include "conf/Config.h"
#include "DefaultConfig.h"

ConfigTreeNode *DefaultConfig::create() {
  ConfigTreeNode *tree = new ConfigTreeNode("root");

  ConfigTreeNode *serverConfig = new ConfigTreeNode("ServerConfig");
  tree->addNode(serverConfig);

  DefaultConfigItem item = getDefault(Port);
  ConfigTreeNode *port = new ConfigTreeNode("Port");
  port->addValue(item.value);
  port->setComment(item.comment);
  serverConfig->addNode(port);

  item = getDefault(SslCert);
  ConfigTreeNode *sslCert = new ConfigTreeNode("SslCert");
  sslCert->addValue(item.value);
  sslCert->setComment(item.comment);
  serverConfig->addNode(sslCert);

  item = getDefault(SslKey);
  ConfigTreeNode *sslKey = new ConfigTreeNode("SslKey");
  sslKey->addValue(item.value);
  sslKey->setComment(item.comment);
  serverConfig->addNode(sslKey);    

  return tree;
}

DefaultConfigItem DefaultConfig::getDefault(DefaultConfigItemName name) {
  DefaultConfigItem item;

  switch (name) {
  case Port:
    item.value = 4512;
    item.comment = "The port the server should bind to.";
    break;

  case SslCert:
    item.value = "FILL ME OUT";
    item.comment = "The certificate the server should use for SSL.";
    break;

  case SslKey:
    item.value = "FILL ME OUT";
    item.comment = "The private key the server should use for SSL.";
    break;        
  }

  return item;
}
