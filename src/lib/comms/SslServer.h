#ifndef SSL_SERVER_H
#define SSL_SERVER_H

#include <QString>
#include <QTcpServer>

class Connection;

class SslServer : public QTcpServer {
  Q_OBJECT

public:
  SslServer(const QString &cert, const QString &key);

signals:
  void newConnection(Connection *conn);

protected:
  void incomingConnection(int socketDescriptor);

private:
  void setSecurityParameters();
  
  QString cert, key;
};

#endif // SSL_SERVER_H
