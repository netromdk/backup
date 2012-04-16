#ifndef CONFIG_TREE_H
#define CONFIG_TREE_H

#include <QDebug>
#include <QString>
#include <QStringList>

#include "ConfigTreeNode.h"

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

  // Add node at specified point in the tree and returns the node it
  // was added to.
  //ConfigTreeNode *addNode(const QString &path, ConfigTreeNode *node);

  // Add node to root node.
  //ConfigTreeNode *addNode(ConfigTreeNode *node);  
  
  ConfigTreeNode *getRoot() const { return tree; }

  void print(QDebug dbg = QDebug(QtDebugMsg));
    
private:
  QStringList pathToList(const QString &path);
  ConfigTreeNode *traverse(ConfigTreeNode *node, const QString &name);
  
  ConfigTreeNode *tree;
};

#endif // CONFIG_TREE_H
