#ifndef DEFAULT_CONFIG_H
#define DEFAULT_CONFIG_H

#include <QString>
#include <QVariant>

#include "conf/Config.h"
using namespace conf;

enum DefaultConfigItemName {
  Host,
  Port
};

struct DefaultConfigItem {
  QVariant value;
  QString comment;
};

class DefaultConfig {
public:
  /**
   * Create a configuration tree of all the default values.
   */
  static ConfigTreeNode *create();

  /**
   * Retrieve the default value and comment for a given configuration
   * item.
   */
  static DefaultConfigItem getDefault(DefaultConfigItemName name);
};

#endif // DEFAULT_CONFIG_H
