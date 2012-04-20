#ifndef DEFAULT_CONFIG_H
#define DEFAULT_CONFIG_H

#include <QString>
#include <QVariant>

class ConfigTreeNode;

enum DefaultConfigItemName {
  Port,
};

struct DefaultConfigItem {
  QVariant value;
  QString comment;
};

class DefaultConfig {
public:
  static ConfigTreeNode *create();
  static DefaultConfigItem getDefault(DefaultConfigItemName name);
};

#endif // DEFAULT_CONFIG_H
