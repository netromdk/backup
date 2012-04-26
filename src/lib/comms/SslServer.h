#ifndef SSL_SERVER_H
#define SSL_SERVER_H

#include <QString>
#include <QTcpServer>

namespace comms {
  class Connection;

  /**
   * Provides a TCP server for secure communications using SSLv3/TLSv1.
   *
   * Only allows ciphers that use at least 128 bits and disallows all
   * using MD5, RC4 or DES.
   */
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
}

#endif // SSL_SERVER_H
