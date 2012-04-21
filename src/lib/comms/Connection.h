#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSslSocket>

/**
 * Provides a socket using SSL.
 */
class Connection : public QSslSocket {
  Q_OBJECT
  
public:
  /**
   * Creates a socket for client mode.
   */
  Connection();

  /**
   * Creates a socket for server mode.
   */
  Connection(int socketDescriptor, const QString &cert, const QString &key);

private slots:
  void onDisconnected();
  void onDataReady();
  void onEncrypted();
  void onSslErrors(const QList<QSslError> &erros);

  void handshake();

private:
  void init();

  bool serverMode;
};

#endif // CONNECTION_H
