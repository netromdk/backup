#ifndef ENV_H
#define ENV_H

#include <QString>

/**
 * Interface with the system environment of variables.
 */
class Env {
public:
  /**
   * Retrieve the environment variable denoted by 'name'. If it is not
   * defined then return 'defaultValue'.
   */
  static QString get(const QString &name, const QString &defaultValue = QString());
};

#endif // ENV_H
