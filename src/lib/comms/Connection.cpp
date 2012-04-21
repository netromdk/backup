#include <QDebug>
#include <QByteArray>
#include <QSslCipher>
#include <QSslConfiguration>

#include "Connection.h"

Connection::Connection() : serverMode(false) {
  init();
}

Connection::Connection(int socketDescriptor, const QString &cert, const QString &key)
  : serverMode(true)
{
  setSocketDescriptor(socketDescriptor);
  init();
  setLocalCertificate(cert);
  setPrivateKey(key);
  handshake();
}

void Connection::onDataReady() {
  QByteArray data = readAll();
  // emit signal here after parsing!
  qDebug() << "got data:" << data;
}

void Connection::onEncrypted() {
  qDebug() << "Socket is encrypted:" << sslConfiguration().sessionCipher();
}

void Connection::onSslErrors(const QList<QSslError> &errors) {
  qWarning() << "ssl errors:" << errors;
}

void Connection::onPeerVerifyError(const QSslError &error) {
  qWarning() << "peer verify error:" << error;
}

void Connection::init() {
  connect(this, SIGNAL(connected()), SLOT(handshake()));  
  connect(this, SIGNAL(readyRead()), SLOT(onDataReady()));
  connect(this, SIGNAL(encrypted()), SLOT(onEncrypted()));
  connect(this, SIGNAL(sslErrors(const QList<QSslError>&)),
          SLOT(onSslErrors(const QList<QSslError>&)));
  connect(this, SIGNAL(peerVerifyError(const QSslError&)),
          SLOT(onPeerVerifyError(const QSslError&)));
}

void Connection::handshake() {
  if (serverMode) {
    startServerEncryption();
  }
  else {
    startClientEncryption();
  }
}
