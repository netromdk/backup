#include "ConfigTree.h"
#include "ConfigTreeNode.h"

ConfigTree::ConfigTree(const QString &name) : tree(new ConfigTreeNode(name)) { }
   
ConfigTree::~ConfigTree() {
  if (tree) {
    delete tree;
  }
}

ConfigTreeNode *ConfigTree::getNode(const QString &path) {
  QStringList elms = pathToList(path);
  if (elms.size() == 0) {
    return NULL;
  }

  // Walk the path and find the node list.
  ConfigTreeNode *node = tree;
  while (elms.size() > 0) {
    QString part = elms.takeFirst();
    node = traverse(node, part);
    if (!node) {
      return NULL;
    }
  }

  return node;
}

bool ConfigTree::getNodes(const QString &path, ConfigTreeNodeList &nodes) {
  ConfigTreeNode *node = getNode(path);
  if (node) {
    nodes = node->getNodes();
    return true;
  }
  return false;
}

void ConfigTree::addNode(ConfigTreeNode *node) {
  tree->addNode(node);
}

ConfigTreeNode *ConfigTree::addNode(const QString &path, ConfigTreeNode *node) {
  ConfigTreeNode *elm = getNode(path);
  if (!elm) return NULL;
  elm->addNode(node);
  return elm;
}

void ConfigTree::print(QDebug dbg) {
  tree->print(dbg);
}

QStringList ConfigTree::pathToList(const QString &path) {
  QStringList elms = path.split("/", QString::SkipEmptyParts);
  if (elms.size() == 0) {
    return elms;
  }
  if (elms[0] == tree->getName()) {
    elms.removeFirst();
  }
  return elms;
}

ConfigTreeNode *ConfigTree::traverse(ConfigTreeNode *node, const QString &name) {
  if (!node) return NULL;

  foreach (ConfigTreeNode *elm, node->getNodes()) {
    if (elm->getName() == name) {
      return elm;
    }
  }

  return NULL;
}
