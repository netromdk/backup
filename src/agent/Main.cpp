#include <QList>
#include <QDebug>
#include <QCoreApplication>

#include <signal.h>

#include "Agent.h"
#include "Version.h"

Agent *agent = NULL;

void signalHandler(int signal) {
  static QList<int> sup = QList<int>() << SIGABRT << SIGTERM << SIGINT << SIGKILL;
  if (!sup.contains(signal)) {
    qWarning() << "Caught unsupported signal:" << signal;
    return;
  }

  qDebug() << "Caught signal. Terminating..";
  
  if (agent) {
    delete agent;
    agent = NULL;
  }
    
  QCoreApplication::exit(0);
}

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

 // Register signals for cleanup.
  signal(SIGABRT, &signalHandler);
	signal(SIGTERM, &signalHandler);
	signal(SIGINT, &signalHandler);

#ifndef WIN
  // SIGKILL is not available on Windows.
	signal(SIGKILL, &signalHandler);
#endif    

  qDebug() << "Starting backup agent -" << qPrintable(versionString());
  agent = new Agent;
  
  return app.exec();
}
