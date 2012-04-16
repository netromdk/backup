#ifndef CONFIG_PATH_H
#define CONFIG_PATH_H

#include <QDebug>
#include <QString>

#include "ConfigPathElement.h"

/**
 * DESCRIBE ME!
 */
class ConfigPath {
public:
  ConfigPath();
  ConfigPath(const char *path);  
  ConfigPath(const QString &path);
  virtual ~ConfigPath();
  
  QString toString() const;

  // Methods for adding elements directly.

  ConfigPathElement *next();

private:
  void clear();
  void parse(const QString &path);
  
  ConfigPathList pathList;
};

inline QDebug operator<<(QDebug debug, const ConfigPath &path) {
  debug << path.toString();
  return debug;
}

#endif // CONFIG_PATH_H
