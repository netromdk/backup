#ifndef ENV_H
#define ENV_H

#include <QString>

/**
 * Interface with the system environment of variables.
 */
class Env {
public:
  static QString get(const QString &name);
};

#endif // ENV_H
