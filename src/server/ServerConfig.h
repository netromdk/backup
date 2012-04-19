#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <QDebug>

class ConfigTreeNode;

class ServerConfig {
public:
  ServerConfig();
  virtual ~ServerConfig();

  QString getPath() const { return path; }
  ConfigTreeNode *getRoot() const { return tree; }

  void print(QDebug dbg = QDebug(QtDebugMsg)) const;  
  
private:
  QString path;
  ConfigTreeNode *tree;
};

inline QDebug operator<<(QDebug debug, const ServerConfig &conf) {
  conf.print(debug);
  return debug;
}

#endif // SERVER_CONFIG_H
