#include <QProcessEnvironment>

#include "Env.h"

QString Env::get(const QString &name, const QString &defaultValue) {
  return QProcessEnvironment::systemEnvironment().value(name, defaultValue);
}
