#include <QDebug>
#include <QCoreApplication>

#include "Server.h"
#include "Version.h"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  qDebug() << "Starting backup server -" << qPrintable(versionString());
  Server server;
  
  return app.exec();
}
