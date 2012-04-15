#ifndef CONFIG_TREE_H
#define CONFIG_TREE_H

/*
  Should also have methods for accessing leafs smartly, like
  "ServerConfig.Agents" to retrieve a list of leafs at that point in
  the tree.
 */

#include <QString>

class ConfigTreeNode;

class ConfigTree {
public:
  ConfigTree(const QString &name = QString("root"));
  virtual ~ConfigTree();
  
  // Add node at specified point in the tree and returns the node it
  // was added to.
  //ConfigTreeNode *addNode(const QString &path, ConfigTreeNode *node);

  // Add node to root node.
  //ConfigTreeNode *addNode(ConfigTreeNode *node);

  // Get node list from path.
  //ConfigTreeNodeList getNode(const QString &path);
  
  ConfigTreeNode *getRoot() const { return tree; }
    
private:
  ConfigTreeNode *tree;
};

#endif // CONFIG_TREE_H
