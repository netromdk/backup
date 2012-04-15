#include <QDebug>
#include <QCoreApplication>

#include "Version.h"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  qDebug() << "Starting backup server -" << versionString().toUtf8().constData();
  
  return app.exec();
}
