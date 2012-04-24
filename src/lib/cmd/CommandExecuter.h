#ifndef COMMAND_EXECUTER_H
#define COMMAND_EXECUTER_H

#include <QString>
#include <QStringList>

#include "CommandOption.h"

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
  bool checkOptionType(const QString &token, CommandOption *option, QVariant &var);
  
  CommandTreeNode *tree;

  // State for executing commands.
  int lastToken;
  OptionMap options;
  QStringList posCmds, extData;  
};

#endif // COMMAND_EXECUTER_H
