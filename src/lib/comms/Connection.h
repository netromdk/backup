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

signals:
  /**
   * This signal is emitted when the channel is encrypted and ready to
   * send and receive data.
   */
  void ready();

private slots:
  void onDataReady();
  void onEncrypted();
  void onSslErrors(const QList<QSslError> &erros);

  void handshake();

private:
  void init();

  bool serverMode;
};

#endif // CONNECTION_H
