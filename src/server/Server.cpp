#include <QDebug>
#include <QCoreApplication>

#include "Server.h"
#include "ServerConfig.h"
#include "comms/SslServer.h"

Server::Server() : config(new ServerConfig), server(NULL) {
  if (!config->isValid()) {
    QCoreApplication::exit(-1);
    exit(-1);
  }
  qDebug() << "Loaded conf:" << qPrintable(config->getPath());

  server = new SslServer;
  if (!server->listen(QHostAddress::Any, config->getPort())) {
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
