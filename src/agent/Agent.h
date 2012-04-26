#ifndef AGENT_H
#define AGENT_H

#include <QObject>

#include "comms/Connection.h"
#include "comms/StatePacket.h"
using namespace comms;

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
