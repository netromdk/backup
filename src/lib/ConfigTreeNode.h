#ifndef CONFIG_TREE_NODE_H
#define CONFIG_TREE_NODE_H

#include <QList>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariantList>

class ConfigTreeNode;
typedef QList<ConfigTreeNode*> ConfigTreeNodeList;

/**
 * The ConfigTreeNode class provides a way to represent a
 * configuration file in a tree structure. Each node in the tree has a
 * name associated to it, and both nodes and leaves can have QVariant
 * values stored with them.
 *
 * Paths can be used to easily search the tree. These are of the form
 * "name/name2/name3/..". It will start by looking in the root nodes
 * to see if it can find "name" then search for "name2" in that
 * subtree etc. The name of the root will always be ignored if
 * supplied in the path.
 */
class ConfigTreeNode {
public:
  ConfigTreeNode(const QString &name);
  virtual ~ConfigTreeNode();

  QString getName() const { return name; }

  void addNode(ConfigTreeNode *node) { nodes.append(node); }
  ConfigTreeNodeList getNodes() const { return nodes; }

  /**
   * Search for the node for the given path.
   */
  ConfigTreeNode *searchNode(const QString &path);  

  /**
   * Search for the node list for the given path. Returns false if
   * nothing was found.
   */
  bool searchNodes(const QString &path, ConfigTreeNodeList &nodes);  

  void addValue(const QVariant &value) { values.append(value); }
  void setValues(const QVariantList &values) { this->values = values; }
  QVariantList &getValues() { return values; }
  QVariantList getValues() const { return values; }

  void print(QDebug dbg = QDebug(QtDebugMsg), int depth = 0);

private:
  QStringList pathToList(const QString &path);
  ConfigTreeNode *traverse(ConfigTreeNode *node, const QString &name);
  
  QString name;
  ConfigTreeNodeList nodes;
  QVariantList values;
};

#endif // CONFIG_TREE_NODE_H
