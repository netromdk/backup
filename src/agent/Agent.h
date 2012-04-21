#ifndef AGENT_H
#define AGENT_H

#include <QObject>

class Connection;
class StatePacket;
class AgentConfig;

class Agent : public QObject {
  Q_OBJECT
  
public:
  Agent();
  virtual ~Agent();

private slots:
  void onConnectionReady();
  void onConnectionDisconnected();
  void onPacketReceived(StatePacket *packet);
  
private:
  AgentConfig *config;
  Connection *conn;
};

#endif // AGENT_H
