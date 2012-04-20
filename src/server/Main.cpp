#include <QDebug>
#include <QCoreApplication>

#include "Version.h"
#include "ServerConfig.h"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  qDebug() << "Starting backup server -" << qPrintable(versionString());

  ServerConfig conf;
  if (!conf.isValid()) {
    return -1;
  }
  qDebug() << "Loaded conf:" << conf.getPath();
  qDebug() << conf;

  qDebug() << "port:" << conf.getPort();

  return app.exec();
}
