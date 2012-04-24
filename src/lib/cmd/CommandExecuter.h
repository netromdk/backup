#ifndef COMMAND_EXECUTER_H
#define COMMAND_EXECUTER_H

#include <QString>
#include <QStringList>
#include <QVariantMap>

#include "CommandType.h"

class CommandTreeNode;

class CommandExecuter {
public:
  CommandExecuter(CommandTreeNode *tree);

  bool execute(const QString &input);

private:
  QStringList parse(const QString &input);
  void clearState();
  CommandTreeNode *traverse(CommandTreeNode *node, QStringList &tokens, uint pos = 0);
  bool parseOption(QString token, QStringList &optToks);
  bool checkType(const QString &token, CommandType type, QVariant &var);
  
  CommandTreeNode *tree;

  // State for executing commands.
  int lastToken;
  QVariantMap options;
  QVariantList posCmds;
  QStringList extData;  
};

#endif // COMMAND_EXECUTER_H
