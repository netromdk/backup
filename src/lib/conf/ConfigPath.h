#ifndef CONFIG_PATH_H
#define CONFIG_PATH_H

#include <QDebug>
#include <QString>

#include "ConfigPathElement.h"

/**
 * A ConfigPath is used to search a tree of ConfigTreeNode elements.
 *
 * The path itself consists internally of ConfigPathElement objects
 * (either ConfigPathElementName or ConfigPathElementQuantifier).
 *
 * A string representation is used for this configuration path. An
 * example would be "/Foo/Bar/Baz" which will try to locate the node
 * with the name "Foo", then it will locate "Bar" in the sub tree of
 * "Foo" and finally look for "Bar" in that sub tree. Note that "/" is
 * always the path delimiter. Using quantifiers one could write
 * "/Foo/[0]/[*]" which will take the first child of "Foo" and all the
 * children of this sub tree (due to the Kleene star). The quantifier
 * can also use lists and ranges; "/Foo/[1,2]/[8-11]" will take the
 * second and third child of "Foo" and from each of these it will take
 * the 9th through 12th child.
 */
class ConfigPath {
public:
  ConfigPath();
  ConfigPath(const char *path);  
  ConfigPath(const QString &path);
  virtual ~ConfigPath();
  
  QString toString() const;

  // TODO: Methods for adding elements directly.

  /**
   * Removes the first element from the list of elements and returns
   * it.
   */
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
