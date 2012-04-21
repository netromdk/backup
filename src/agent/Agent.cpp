#include <QDebug>
#include <QCoreApplication>

#include "Agent.h"
#include "AgentConfig.h"
#include "comms/Connection.h"
#include "comms/StatePacket.h"

Agent::Agent() : config(new AgentConfig), conn(NULL) {
  if (!config->isValid()) {
    QCoreApplication::exit(-1);
    exit(-1);
  }
  qDebug() << "Loaded conf:" << qPrintable(config->getPath());

  conn = new Connection;
  connect(conn, SIGNAL(ready()), SLOT(onConnectionReady()));
  connect(conn, SIGNAL(disconnected()), SLOT(onConnectionDisconnected()));
  connect(conn, SIGNAL(packetReceived(StatePacket*)),
          SLOT(onPacketReceived(StatePacket*)));
  
  conn->connectToHost(config->getHost(), config->getPort());
  qDebug() << "Connecting to" << qPrintable(config->getHost()) << ":" << config->getPort();  
  if (!conn->waitForConnected()) {
    qCritical() << "Could not connect to" << qPrintable(config->getHost()) << ":" << config->getPort();
    QCoreApplication::exit(-1);
    exit(-1);    
  }
  qDebug() << "Connection established.";
}

Agent::~Agent() {
  delete config;
  if (conn) {
    delete conn;
  }
}

void Agent::onConnectionReady() {
  qDebug() << "Ready to proceed.";
  // initiate auth protocol here
}

void Agent::onConnectionDisconnected() {
  qDebug() << "Disconnected from server.";
}

void Agent::onPacketReceived(StatePacket *packet) {
  qDebug() << "Received packet.";
  qDebug() << "packet contents:" << packet->getDataMap();

  delete packet;  
}
