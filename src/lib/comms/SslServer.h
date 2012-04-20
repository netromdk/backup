#ifndef SSL_SERVER_H
#define SSL_SERVER_H

#include <QTcpServer>

class Connection;

class SslServer : public QTcpServer {
  Q_OBJECT

protected:
  void incomingConnection(int socketDescriptor);

signals:
  void newConnection(Connection *conn);
};

#endif // SSL_SERVER_H
