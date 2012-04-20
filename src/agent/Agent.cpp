#include <QDebug>
#include <QCoreApplication>

#include "Agent.h"
#include "AgentConfig.h"

Agent::Agent() : config(new AgentConfig) {
  if (!config->isValid()) {
    QCoreApplication::exit(-1);
    exit(-1);
  }
  qDebug() << "Loaded conf:" << qPrintable(config->getPath());

  // create connection.
}

Agent::~Agent() {
  delete config;
}
