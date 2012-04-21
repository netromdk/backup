#include <QDebug>
#include <QCoreApplication>

#include "Server.h"
#include "ServerConfig.h"
#include "comms/SslServer.h"
#include "comms/Connection.h"
#include "comms/StatePacket.h"

Server::Server() : config(new ServerConfig), server(NULL) {
  if (!config->isValid()) {
    QCoreApplication::exit(-1);
    exit(-1);
  }
  qDebug() << "Loaded conf:" << qPrintable(config->getPath());

  server = new SslServer(config->getSslCert(), config->getSslKey());
  connect(server, SIGNAL(newConnection(Connection*)),
          SLOT(onNewConnection(Connection*)));

  if (!server->listen(QHostAddress::AnyIPv6, config->getPort())) {
    qCritical() << "Could not bind server to port" << config->getPort();
    QCoreApplication::exit(-1);
    exit(-1);
  }
  qDebug() << "Server bound to port" << server->serverPort();
}

Server::~Server() {
  delete config;
  if (server) {
    delete server;
  }
}

void Server::onNewConnection(Connection *conn) {
  qDebug() << "New connection from" << qPrintable(conn->peerAddress().toString())
           << ":" << conn->peerPort();

  connect(conn, SIGNAL(disconnected()), SLOT(onConnectionDisconnected()));
  connect(conn, SIGNAL(packetReceived(StatePacket*)),
          SLOT(onPacketReceived(StatePacket*)));  
}

void Server::onConnectionDisconnected() {
  Connection *conn = qobject_cast<Connection*>(sender());
  if (!conn) return;

  qDebug() << "Disconnect from" << qPrintable(conn->peerAddress().toString())
           << ":" << conn->peerPort();
}

void Server::onPacketReceived(StatePacket *packet) {
  Connection *conn = qobject_cast<Connection*>(sender());
  if (!conn) return;

  qDebug() << "Received packet from" << qPrintable(conn->peerAddress().toString())
           << ":" << conn->peerPort();

  qDebug() << "packet contents:" << packet->getDataMap();

  delete packet;
}
