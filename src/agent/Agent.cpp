#include <QDebug>
#include <QCoreApplication>

#include "Agent.h"
#include "AgentConfig.h"
#include "comms/Connection.h"

Agent::Agent() : config(new AgentConfig) {
  if (!config->isValid()) {
    QCoreApplication::exit(-1);
    exit(-1);
  }
  qDebug() << "Loaded conf:" << qPrintable(config->getPath());

  conn = new Connection;
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
}
