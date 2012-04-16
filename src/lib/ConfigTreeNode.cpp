#include <QDebug>
#include <QtAlgorithms>

#include "ConfigTreeNode.h"

ConfigTreeNode::ConfigTreeNode(const QString &name) : name(name) { }

ConfigTreeNode::~ConfigTreeNode() {
  if (nodes.size() > 0) {
    qDeleteAll(nodes);
  }
}

ConfigTreeNode *ConfigTreeNode::searchNode(const QString &path) {
 QStringList elms = pathToList(path);
  if (elms.size() == 0) {
    return NULL;
  }

  // Walk the path and find the node list.
  ConfigTreeNode *node = this;
  while (elms.size() > 0) {
    QString part = elms.takeFirst();
    node = traverse(node, part);
    if (!node) {
      return NULL;
    }
  }

  return node;  
}

bool ConfigTreeNode::searchNodes(const QString &path, ConfigTreeNodeList &nodes) {
  ConfigTreeNode *node = searchNode(path);
  if (node) {
    nodes = node->getNodes();
    return true;
  }
  return false;  
}

void ConfigTreeNode::print(QDebug dbg, int depth) {
  QString pad = "";
  for (int i = 0; i < depth; i++) {
    pad += "  ";
  }
  
  dbg.nospace() << qPrintable(pad) << qPrintable(name);
  if (values.size() > 0) {
    dbg.space() << "=" << values;
  }
  dbg.nospace() << "\n";

  depth++;
  foreach (ConfigTreeNode *node, nodes) {
    node->print(dbg, depth);
  }
}

QStringList ConfigTreeNode::pathToList(const QString &path) {
  QStringList elms = path.split("/", QString::SkipEmptyParts);
  if (elms.size() == 0) {
    return elms;
  }

  // Ignore my own name if it occurs.
  if (elms[0] == name) {
    elms.removeFirst();
  }
  
  return elms;
}

ConfigTreeNode *ConfigTreeNode::traverse(ConfigTreeNode *node, const QString &name) {
  if (!node) return NULL;

  foreach (ConfigTreeNode *elm, node->getNodes()) {
    if (elm->getName() == name) {
      return elm;
    }
  }

  return NULL;
}
