#ifndef CONFIG_TREE_NODE_H
#define CONFIG_TREE_NODE_H

#include <QList>
#include <QDebug>
#include <QString>
#include <QVariantList>

#include "ConfigPath.h"

class ConfigTreeNode;
typedef QList<ConfigTreeNode*> ConfigTreeNodeList;

class ConfigPathElement;

/**
 * Provides a way to represent a configuration file in a tree
 * structure. Each node in the tree has a name associated to it, and
 * both nodes and leaves can have QVariant values stored with them.
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

  bool hasComment() const { return !comment.isEmpty(); }
  void setComment(const QString &comment) { this->comment = comment; }
  QString getComment() const { return comment; }

  void addNode(ConfigTreeNode *node) { nodes.append(node); }
  ConfigTreeNodeList getNodes() const { return nodes; }

  /**
   * Search for the nodes of the given path.
   */
  ConfigTreeNodeList searchNodes(ConfigPath path);

  /**
   * Search for the node of the given path.
   */
  ConfigTreeNode *searchNode(ConfigPath path);  

  void addValue(const QVariant &value) { values.append(value); }
  void setValues(const QVariantList &values) { this->values = values; }
  QVariantList getValues() { return values; }
  const QVariantList &getValues() const { return values; }
  QVariant getValue() const;

  void print(QDebug dbg = QDebug(QtDebugMsg), int depth = 0) const;

private:
  ConfigTreeNodeList traverse(ConfigTreeNodeList &nodeList,
                              ConfigPathElement *configElm);
  
  QString name, comment;
  ConfigTreeNodeList nodes;
  QVariantList values;
};

inline QDebug operator<<(QDebug debug, const ConfigTreeNode &node) {
  node.print(debug);
  return debug;
}

inline QDebug operator<<(QDebug debug, const ConfigTreeNode *node) {
  node->print(debug);
  return debug;
}

#endif // CONFIG_TREE_NODE_H
