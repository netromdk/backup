#include <QStringList>
#include <QtAlgorithms>

#include "ConfigPath.h"
#include "ConfigPathElement.h"

namespace conf {
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

    foreach (const QString &elm, elms) {
      if (ConfigPathElementQuantifier::regexp.exactMatch(elm)) {
        pathList.append(new ConfigPathElementQuantifier(elm));      
      }
      else {
        pathList.append(new ConfigPathElementName(elm));
      }
    }
  }
}
