#ifndef CONFIG_TREE_H
#define CONFIG_TREE_H

#include <QDebug>
#include <QString>
#include <QStringList>

#include "ConfigTreeNode.h"

/**
 * The ConfigTree class provides a way to represent a configuration
 * file in a tree structure. Each node in the tree has a name
 * associated to it, and both nodes and leaves can have QVariant
 * values stored with them.
 *
 * Paths can be used to easily search the tree. These are of the form
 * "name/name2/name3/..". It will start by looking in the root nodes
 * to see if it can find "name" then search for "name2" in that
 * subtree etc. The name of the root will always be ignored if
 * supplied in the path.
 */
class ConfigTree {
public:
  ConfigTree(const QString &name = QString("root"));
  virtual ~ConfigTree();

  /**
   * Get the node for the given path.
   */
  ConfigTreeNode *getNode(const QString &path);  

  /**
   * Get node list for the given path. Returns false if nothing was
   * found.
   */
  bool getNodes(const QString &path, ConfigTreeNodeList &nodes);

  /**
   * Add node to root node.
   */
  void addNode(ConfigTreeNode *node);

  /**
   * Add node at specified point in the tree and returns the node it
   * was added to.
   */
  ConfigTreeNode *addNode(const QString &path, ConfigTreeNode *node);  
  
  ConfigTreeNode *getRoot() const { return tree; }

  void print(QDebug dbg = QDebug(QtDebugMsg));
    
private:
  QStringList pathToList(const QString &path);
  ConfigTreeNode *traverse(ConfigTreeNode *node, const QString &name);
  
  ConfigTreeNode *tree;
};

#endif // CONFIG_TREE_H
