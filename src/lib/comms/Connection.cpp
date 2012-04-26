#include <QDebug>
#include <QByteArray>
#include <QSslCipher>
#include <QSslConfiguration>

#include "Packet.h"
#include "Connection.h"
#include "StatePacket.h"

namespace comms {
  Connection::Connection() : serverMode(false), readSize(0) {
    init();
  }

  Connection::Connection(int socketDescriptor, const QString &cert, const QString &key)
    : serverMode(true), readSize(0)
  {
    setSocketDescriptor(socketDescriptor);
    setLocalCertificate(cert);
    setPrivateKey(key);
  
    init();
    handshake();
  }

  void Connection::sendPacket(Packet *packet) {
    packetQueue.enqueue(packet);

    if (packetQueue.size() == 1) {
      sendNext();
    }
  }

  void Connection::onDataReady() {
    buffer = readAll();

    // The TCP protocol might stack multiple packets into a bigger one
    // if the packets are sufficiently small. Therefore, we have to keep
    // reading until we are sure we have received it all.
  
  start:
    if (readSize == 0) {
      // Wait until we have enough data to read the 32-bit int.
      if (buffer.size() < sizeof(readSize)) {
        return;
      }

      QDataStream stream(&buffer, QIODevice::ReadOnly);
      stream >> readSize;

      // Remove the data of the size just read from the buffer.
      buffer = buffer.mid(sizeof(readSize));
    }

    if (buffer.size() == readSize) {
      emit packetReceived(StatePacket::fromData(buffer.left(readSize)));
      buffer = buffer.mid(readSize);
      readSize = 0;

      // See if there's more.
      goto start;
    }
  }

  void Connection::onEncrypted() {
    qDebug() << "Socket is encrypted:" << sslConfiguration().sessionCipher();
    emit ready();
  }

  void Connection::onSslErrors(const QList<QSslError> &errors) {
    qWarning() << "ssl errors:" << errors;

    // Ignore self-signed cert errors.
    QList<QSslError> expectedErrors;
    foreach (QSslError error, errors) {
      if (error.error() == QSslError::SelfSignedCertificate) {
        expectedErrors.append(error);
      }
    }
    ignoreSslErrors(expectedErrors);
  }

  void Connection::init() {
    connect(this, SIGNAL(connected()), SLOT(handshake()));
    connect(this, SIGNAL(readyRead()), SLOT(onDataReady()));
    connect(this, SIGNAL(encrypted()), SLOT(onEncrypted()));
    connect(this, SIGNAL(sslErrors(const QList<QSslError>&)),
            SLOT(onSslErrors(const QList<QSslError>&)));
    connect(this, SIGNAL(bytesWritten(qint64)), SLOT(sendNext(qint64)));  
  }

  void Connection::handshake() {
    if (serverMode) {
      startServerEncryption();
    }
    else {
      startClientEncryption();
    }
  }

  void Connection::sendNext(qint64 bytes) {
    while (!packetQueue.isEmpty() && QSslSocket::state() == ConnectedState) {
      Packet *packet = packetQueue.head();
      QByteArray data = packet->getData();

      // If we have transferred it all then delete the packet.
      if (data.size() == 0) {
        delete packetQueue.dequeue();
        continue;
      }

      write(data);
      return;
    }
  }
}
