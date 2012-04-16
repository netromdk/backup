#include <QDebug>
#include <QStringList>
#include <QtAlgorithms>

#include "ConfigTreeNode.h"

ConfigTreeNode::ConfigTreeNode(const QString &name) : name(name) { }

ConfigTreeNode::~ConfigTreeNode() {
  qDeleteAll(nodes);
  nodes.clear();
}

ConfigTreeNodeList ConfigTreeNode::searchNodes(ConfigPath path) {
  ConfigTreeNodeList candidates;
  candidates.append(this);

  ConfigPathElement *configElm;
  while ((configElm = path.next())) {
    candidates = traverse(candidates, configElm);
    if (candidates.size() == 0) {
      return candidates;
    }
  }

  return candidates;
}

ConfigTreeNode *ConfigTreeNode::searchNode(ConfigPath path) {
  ConfigTreeNodeList list = searchNodes(path);
  if (list.size() > 0) {
    return list[0];
  }
  return NULL;
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
  for (int i = 0; i < nodes.size(); i++) {
    ConfigTreeNode *node = nodes[i];
    node->print(dbg, depth);

    // Add a line break in the end if this node had a comment - it is
    // more readable.
    if (node->hasComment() && nodes.size() > 1 && i < nodes.size() - 1) {
      dbg.nospace() << "\n";
    }
  }
}

ConfigTreeNodeList ConfigTreeNode::traverse(ConfigTreeNodeList &nodeList,
                                            ConfigPathElement *configElm) {
  if (nodeList.size() == 0) {
    return nodeList;
  }

  ConfigTreeNodeList res;
  foreach (ConfigTreeNode *elm, nodeList) {
    switch (configElm->getKind()) {
    case ConfigPathElement::Name: {
      foreach (ConfigTreeNode *subelm, elm->getNodes()) {
        QString elmName = dynamic_cast<ConfigPathElementName*>(configElm)->getName();
        if (subelm->getName() == elmName) {
          res.append(subelm);
        }
      }
      break;
    }

    case ConfigPathElement::Quantifier:
      break;        
    }    
  }

  return res;
}
