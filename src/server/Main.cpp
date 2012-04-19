#include <QDebug>
#include <QCoreApplication>

#include "Version.h"
#include "ServerConfig.h"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  qDebug() << "Starting backup server -" << qPrintable(versionString());

  ServerConfig conf;
  qDebug() << conf;

  return app.exec();
}
