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

void ConfigTreeNode::print(QDebug dbg, int depth) const {
  QString pad = "";
  for (int i = 0; i < depth; i++) {
    pad += "  ";
  }

  // Write the comment if the node has one assigned. If it is a
  // multiline comment then make each line appear at the same depth as
  // the element itself.
  if (hasComment()) {
    bool multiline = comment.count("\n") > 1;
    dbg.nospace() << qPrintable(pad);
    if (!multiline) {
      dbg.nospace() << "//" << qPrintable(comment);
    }
    else {
      QString cmt;
      QStringList lines = comment.split("\n");
      for (int i = 0; i < lines.size(); i++) {
        QString line = lines[i].trimmed(), ipad = pad;
        bool notLast = (i < lines.size() - 1);
        if (notLast) {
          ipad += "  ";
        }
        cmt += ipad + line;
        if (notLast) {
          cmt += "\n";
        }
      }
      dbg.nospace() << "/*" << qPrintable(cmt) << "*/";
    }
    dbg.nospace() << "\n";      
  }

  // Write the name of the node.
  dbg.nospace() << qPrintable(pad) << qPrintable(name);

  // If any values are assigned then write them out.
  if (values.size() > 0) {
    dbg.space() << "=" << values;
  }
  dbg.nospace() << "\n";

  depth++;
  //foreach (ConfigTreeNode *node, nodes) {
  for (int i = 0; i < nodes.size(); i++) {
    ConfigTreeNode *node = nodes[i];
    node->print(dbg, depth);

    if (node->hasComment() && nodes.size() > 1 && i < nodes.size() - 1) {
      dbg.nospace() << "\n";
    }
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
