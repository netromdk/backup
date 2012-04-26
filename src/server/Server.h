#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include "comms/SslServer.h"
#include "comms/Connection.h"
#include "comms/StatePacket.h"
using namespace comms;

class ServerConfig;

class Server : public QObject {
  Q_OBJECT
  
public:
  Server();
  virtual ~Server();

private slots:
  void onNewConnection(Connection *conn);
  void onConnectionDisconnected();
  void onPacketReceived(StatePacket *packet);
  
private:
  ServerConfig *config;
  SslServer *server;
};

#endif // SERVER_H
