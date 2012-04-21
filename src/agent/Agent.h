#ifndef AGENT_H
#define AGENT_H

#include <QObject>

class Connection;
class AgentConfig;

class Agent : public QObject {
  Q_OBJECT
  
public:
  Agent();
  virtual ~Agent();

private slots:
  void onConnectionReady();
  
private:
  AgentConfig *config;
  Connection *conn;
};

#endif // AGENT_H
