#ifndef COMMAND_EXECUTER_H
#define COMMAND_EXECUTER_H

#include <QString>
#include <QStringList>
#include <QVariantMap>

#include "CommandType.h"

class CommandTreeNode;

/**
 * Provides a command executer that takes input of strings of commands
 * and interprets them using the given command tree. When a match is
 * found the node in question will have its CommandTreeNode::execute
 * method called, with the options, positional commands and extra
 * data, which in turn calls the associated CommandFunction::execute
 * method.
 */ 
class CommandExecuter {
public:
  CommandExecuter(const CommandTreeNode *tree);

  bool execute(const QString &input);

private:
  QStringList parse(const QString &input, bool ignoreLongOpt = true);
  void clearState();
  const CommandTreeNode *traverse(const CommandTreeNode *node, QStringList &tokens, uint pos = 0);
  bool parseOption(QString token, bool &longOpt, QStringList &optToks);
  bool checkType(const QString &token, CommandType type, QVariant &var);
  
  const CommandTreeNode *tree;

  // State for executing commands.
  int lastToken;
  QVariantMap options;
  QVariantList posCmds;
  QStringList extData;  
};

#endif // COMMAND_EXECUTER_H
