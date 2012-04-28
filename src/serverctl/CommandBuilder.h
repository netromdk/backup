#ifndef COMMAND_BUILDER_H
#define COMMAND_BUILDER_H

#include "cmd/CommandTreeNode.h"
using namespace cmd;

class HelpContext;
class AgentContext;

class CommandBuilder {
public:
  CommandBuilder();
  virtual ~CommandBuilder();

  const CommandTreeNode *getRootNode() const { return tree; }

private:
  void build();

  CommandTreeNode *tree;
  HelpContext *helpCtx;
  AgentContext *agentCtx;
};

#endif // COMMAND_BUILDER_H
