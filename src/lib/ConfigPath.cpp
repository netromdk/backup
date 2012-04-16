#include <QStringList>
#include <QtAlgorithms>

#include "ConfigPath.h"
#include "ConfigPathElement.h"

ConfigPath::ConfigPath() { }

ConfigPath::ConfigPath(const char *path) {
  parse(path);
}

ConfigPath::ConfigPath(const QString &path) {
  parse(path);
}

ConfigPath::~ConfigPath() {
  clear();
}

QString ConfigPath::toString() const {
  QString path;
  foreach (const ConfigPathElement *elm, pathList) {
    path += elm->toString() + "/";
  }
  if (path.endsWith("/")) {
    path.chop(1);
  }
  return path;
}

ConfigPathElement *ConfigPath::next() {
  if (pathList.size() == 0) {
    return NULL;
  }

  return pathList.takeFirst();
}

void ConfigPath::clear() {
  qDeleteAll(pathList);
  pathList.clear();
}

void ConfigPath::parse(const QString &path) {
  clear();

  QStringList elms = path.split("/", QString::SkipEmptyParts);
  if (elms.size() == 0) {
    return;
  }

  qDebug() << "config elms:" << elms;

  foreach (const QString &elm, elms) {
    qDebug() << "config elm:" << elm;
    
    // Is it a quantifier?
    if (false) {
      // Skip for now.
    }

    // Otherwise it's a name.
    else {
      pathList.append(new ConfigPathElementName(elm));
    }
  }
}
