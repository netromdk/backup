#ifndef PATHS_H
#define PATHS_H

#include <QString>

/**
 * Access system-specific paths.
 */
class Paths {
public:
  /**
   * The configuration directory.
   */
  static QString getConfigDir();

private:
  static QString configDir;
};

#endif // PATHS_H
