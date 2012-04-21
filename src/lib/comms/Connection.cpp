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
  setLocalCertificate(cert);
  setPrivateKey(key);
  
  init();
  handshake();
}

void Connection::onDisconnected() {
  qDebug() << "Disconnected.";
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
  connect(this, SIGNAL(disconnected()), SLOT(onDisconnected()));    
  connect(this, SIGNAL(readyRead()), SLOT(onDataReady()));
  connect(this, SIGNAL(encrypted()), SLOT(onEncrypted()));
  connect(this, SIGNAL(sslErrors(const QList<QSslError>&)),
          SLOT(onSslErrors(const QList<QSslError>&)));
}

void Connection::handshake() {
  if (serverMode) {
    startServerEncryption();
  }
  else {
    startClientEncryption();
  }
}
