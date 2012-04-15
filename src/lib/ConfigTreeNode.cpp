#include <QDebug>
#include <QtAlgorithms>

#include "ConfigTreeNode.h"

ConfigTreeNode::ConfigTreeNode(const QString &name) : name(name) { }

ConfigTreeNode::~ConfigTreeNode() {
  if (nodes.size() > 0) {
    qDeleteAll(nodes);
  }
}

void ConfigTreeNode::print(int depth, QDebug dbg) {
  QString pad = "";
  for (int i = 0; i < depth; i++) {
    pad += "  ";
  }
  
  dbg.nospace() << qPrintable(pad) << qPrintable(name);
  if (values.size() > 0) {
    dbg.space() << "=" << values;
  }
  dbg << "\n";
  
  depth++;
  foreach (ConfigTreeNode *node, nodes) {
    node->print(depth, dbg);
  }
}
