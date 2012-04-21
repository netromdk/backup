#ifndef CONNECTION_H
#define CONNECTION_H

#include <QQueue>
#include <QByteArray>
#include <QSslSocket>

class Packet;
class StatePacket;

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

  void sendPacket(Packet *packet);

signals:
  /**
   * This signal is emitted when the channel is encrypted and ready to
   * send and receive data.
   */
  void ready();

  void packetReceived(StatePacket *packet);

private slots:
  void onDataReady();
  void onEncrypted();
  void onSslErrors(const QList<QSslError> &erros);

  void handshake();
  void sendNext(qint64 bytes = 0);

private:
  void init();

  bool serverMode;
  QQueue<Packet*> packetQueue;
  QByteArray buffer;
  qint32 readSize;
};

#endif // CONNECTION_H
