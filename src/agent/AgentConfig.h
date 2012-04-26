#ifndef AGENT_CONFIG_H
#define AGENT_CONFIG_H

#include <QDebug>
#include <QString>

#include "conf/Config.h"
using namespace conf;

class AgentConfig {
public:
  AgentConfig();
  virtual ~AgentConfig();

  bool isValid() const { return valid; }
  Config::Errors getErrors() const { return config.getErrors(); }
  QString getPath() const { return config.getPath(); }
  ConfigTreeNode *getRoot() const { return tree; }

  bool save();
  void print(QDebug dbg = QDebug(QtDebugMsg)) const;

  quint16 getPort() const { return portVar; }
  QString getHost() const { return hostVar; }
  
private:
  void load();
  void writeDefault();
  
  ConfigTreeNode *tree;
  bool valid;
  Config config;

  quint16 portVar;
  QString hostVar;
};

inline QDebug operator<<(QDebug debug, const AgentConfig &conf) {
  conf.print(debug);
  return debug;
}

#endif // AGENT_CONFIG_H
