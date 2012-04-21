#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <QDebug>

#include "conf/Config.h"

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

  quint16 getPort() const { return portVar; }
  QString getSslCert() const { return sslCertVar; }
  QString getSslKey() const { return sslKeyVar; }  
  
private:
  void load();
  void writeDefault();
  
  ConfigTreeNode *tree;
  bool valid;
  Config config;

  quint16 portVar;
  QString sslCertVar, sslKeyVar;
};

inline QDebug operator<<(QDebug debug, const ServerConfig &conf) {
  conf.print(debug);
  return debug;
}

#endif // SERVER_CONFIG_H
