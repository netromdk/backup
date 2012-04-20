#include <QProcessEnvironment>

#include "Env.h"

QString Env::get(const QString &name) {
  return QProcessEnvironment::systemEnvironment().value(name);
}
