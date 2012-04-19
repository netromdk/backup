#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <QDebug>

#include "config/Config.h"

class ServerConfig {
public:
  ServerConfig();
  virtual ~ServerConfig();

  QString getPath() const { return path; }
  ConfigTreeNode *getRoot() const { return tree; }
  
private:
  QString path;
  ConfigTreeNode *tree;
};

inline QDebug operator<<(QDebug debug, const ServerConfig &conf) {
  debug << "ServerConfig @" << conf.getPath() << "=";
  ConfigTreeNode *tree = conf.getRoot();
  if (tree) tree->print(debug);
  return debug;
}

#endif // SERVER_CONFIG_H
