#include <QDebug>
#include <QCoreApplication>

#include <signal.h>

void signalHandler(int signal) {
  static QList<int> sup = QList<int>() << SIGABRT << SIGTERM << SIGINT << SIGKILL;
  if (!sup.contains(signal)) {
    qWarning() << "Caught unsupported signal:" << signal;
    return;
  }

  qDebug() << "Caught signal. Terminating..";
  
  // Clean what should be cleaned here..
    
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
  
  return app.exec();
}
