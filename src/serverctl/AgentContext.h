#ifndef AGENT_CONTEXT_H
#define AGENT_CONTEXT_H

#include "cmd/CommandFunction.h"
#include "cmd/CommandTreeNode.h"
using namespace cmd;

class AgentContext : public CommandFunction {
public:
  AgentContext() { }
  virtual ~AgentContext() { }

  virtual void execute(const CommandTreeNode *node, QVariantMap &options,
                       QVariantList &posCmds, QStringList &extData);
};

#endif // AGENT_CONTEXT_H
