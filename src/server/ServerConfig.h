#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <QDebug>

#include "config/Config.h"

class ServerConfig {
public:
  ServerConfig();
  virtual ~ServerConfig();

  bool isValid() const { return valid; }
  Config::Errors getErrors() const { return config.getErrors(); }
  QString getPath() const { return config.getPath(); }
  ConfigTreeNode *getRoot() const { return tree; }

  bool save();

  void print(QDebug dbg = QDebug(QtDebugMsg)) const;  
  
private:
  void load();
  
  ConfigTreeNode *tree;
  bool valid;
  Config config;
};

inline QDebug operator<<(QDebug debug, const ServerConfig &conf) {
  conf.print(debug);
  return debug;
}

#endif // SERVER_CONFIG_H
