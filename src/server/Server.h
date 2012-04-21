#ifndef SERVER_H
#define SERVER_H

#include <QObject>

class SslServer;
class Connection;
class StatePacket;
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
