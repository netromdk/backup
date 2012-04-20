#include "SslServer.h"
#include "Connection.h"

void SslServer::incomingConnection(int descriptor) {
  emit newConnection(new Connection(descriptor));
}
