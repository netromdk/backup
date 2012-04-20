#include <QList>
#include <QDebug>
#include <QCoreApplication>

#include <signal.h>

#include "Server.h"
#include "Version.h"

Server *server = NULL;

void signalHandler(int signal) {
  static QList<int> sup = QList<int>() << SIGABRT << SIGTERM << SIGINT << SIGKILL;
  if (!sup.contains(signal)) {
    qWarning() << "Caught unsupported signal:" << signal;
    return;
  }

  qDebug() << "Caught signal. Terminating..";
  
  if (server) {
    delete server;
    server = NULL;
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

  qDebug() << "Starting backup server -" << qPrintable(versionString());
  server = new Server;
  
  return app.exec();
}
