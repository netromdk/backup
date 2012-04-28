#ifndef HELP_CONTEXT_H
#define HELP_CONTEXT_H

#include "cmd/CommandFunction.h"
#include "cmd/CommandTreeNode.h"
using namespace cmd;

class HelpContext : public CommandFunction {
public:
  HelpContext(const CommandTreeNode *tree = NULL);
  virtual ~HelpContext() { }

  virtual void execute(const CommandTreeNode *node, QVariantMap &options,
                       QVariantList &posCmds, QStringList &extData);

private:
  const CommandTreeNode *tree;
};

#endif // HELP_CONTEXT_H
