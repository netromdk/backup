#ifndef CONFIG_TREE_NODE_H
#define CONFIG_TREE_NODE_H

#include <QList>
#include <QDebug>
#include <QString>
#include <QVariantList>

class ConfigTreeNode;
typedef QList<ConfigTreeNode*> ConfigTreeNodeList;

class ConfigTreeNode {
public:
  ConfigTreeNode(const QString &name);
  virtual ~ConfigTreeNode();

  QString getName() const { return name; }

  void addNode(ConfigTreeNode *node) { nodes.append(node); }
  ConfigTreeNodeList getNodes() const { return nodes; }

  void addValue(const QVariant &value) { values.append(value); }
  void setValues(const QVariantList &values) { this->values = values; }
  QVariantList &getValues() { return values; }
  QVariantList getValues() const { return values; }

  void print(int depth = 0, QDebug dbg = QDebug(QtDebugMsg));

private:
  QString name;
  ConfigTreeNodeList nodes;
  QVariantList values;
};

#endif // CONFIG_TREE_NODE_H
