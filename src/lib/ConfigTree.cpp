#include "ConfigTree.h"
#include "ConfigTreeNode.h"

ConfigTree::ConfigTree(const QString &name) : tree(new ConfigTreeNode(name)) { }
   
ConfigTree::~ConfigTree() {
  if (tree) {
    delete tree;
  }
}
