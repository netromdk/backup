#ifndef COMMAND_TREE_NODE_H
#define COMMAND_TREE_NODE_H

#include <QList>
#include <QDebug>
#include <QString>
#include <QStringList>

#include "CommandFunction.h"

class CommandTreeNode;
typedef QList<CommandTreeNode*> CommandTreeNodeList;
typedef QList<CommandOption*> CommandOptionList;

class CommandTreeNode {
public:
  CommandTreeNode(const QString &name = QString(), CommandFunction *func = NULL);
  virtual ~CommandTreeNode();

  QString getName() const { return name; }

  void addNode(CommandTreeNode *node);
  CommandTreeNodeList getNodes() const { return nodes; }

  void addOption(CommandOption *option);
  CommandOptionList getOptions() const { return options; }

  void print(QDebug dbg = QDebug(QtDebugMsg), int depth = 0) const;

  bool hasFunction() const { return func != NULL; }
  void execute(OptionMap &options, QStringList &posCmds, QStringList &extData);

private:
  QString name;
  CommandFunction *func;
  CommandTreeNodeList nodes;
  CommandOptionList options;
};

inline QDebug operator<<(QDebug debug, const CommandTreeNode &node) {
  node.print(debug);
  return debug;
}

inline QDebug operator<<(QDebug debug, const CommandTreeNode *node) {
  node->print(debug);
  return debug;
}

#endif // COMMAND_TREE_NODE_H
