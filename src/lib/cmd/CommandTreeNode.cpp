#include <QtAlgorithms>

#include "CommandTreeNode.h"

CommandTreeNode::CommandTreeNode(const QString &name, CommandFunction *func)
  : name(name), func(func)
{ }

CommandTreeNode::~CommandTreeNode() {
  if (func) {
    delete func;
  }
  
  qDeleteAll(nodes);
}

void CommandTreeNode::addNode(CommandTreeNode *node) {
  nodes.append(node);
}

void CommandTreeNode::print(QDebug dbg, int depth) const {
  QString pad = "";
  for (int i = 0; i < depth; i++) {
    pad += "  ";
  }

  QString n = (name.isEmpty() ? "<no name>" : name);
  dbg.nospace() << qPrintable(pad) << qPrintable(n) << "\n";

  depth++;
  foreach(CommandTreeNode *node, nodes) {
    node->print(dbg, depth);
  }
}

void CommandTreeNode::execute(OptionMap &options, QStringList &posCmds, QStringList &extData) {
  if (hasFunction()) {
    func->execute(this, options, posCmds, extData);
  }
  else {
    qWarning() << getName() << "has no defined function.";
  }
}
