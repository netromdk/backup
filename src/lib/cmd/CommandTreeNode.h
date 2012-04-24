#ifndef COMMAND_TREE_NODE_H
#define COMMAND_TREE_NODE_H

#include <QList>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariantMap>
#include <QVariantList>

class CommandOption;
class CommandFunction;
class CommandTreeNode;
class PositionalCommand;

typedef QList<CommandTreeNode*> CommandTreeNodeList;
typedef QList<CommandOption*> CommandOptionList;
typedef QList<PositionalCommand*> PositionalCommandList;

class CommandTreeNode {
public:
  CommandTreeNode(const QString &name = QString(), CommandFunction *func = NULL);
  virtual ~CommandTreeNode();

  QString getName() const { return name; }

  void addNode(CommandTreeNode *node);
  CommandTreeNodeList getNodes() const { return nodes; }

  void addOption(CommandOption *option);
  CommandOptionList getOptions() const { return options; }

  void addPosCmd(PositionalCommand *posCmd);
  PositionalCommandList getPosCmds() const { return posCmds; }

  void print(QDebug dbg = QDebug(QtDebugMsg), int depth = 0) const;

  bool hasFunction() const { return func != NULL; }
  void execute(QVariantMap &options, QVariantList &posCmds, QStringList &extData);

private:
  QString name;
  CommandFunction *func;
  CommandTreeNodeList nodes;
  CommandOptionList options;
  PositionalCommandList posCmds;
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
