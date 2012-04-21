#include "SslServer.h"
#include "Connection.h"

SslServer::SslServer(const QString &cert, const QString &key)
  : cert(cert), key(key)
{ }

void SslServer::incomingConnection(int descriptor) {
  emit newConnection(new Connection(descriptor, cert, key));
}
