#include <QDebug>

#include "AgentContext.h"

void AgentContext::execute(const CommandTreeNode *node, QVariantMap &options,
                          QVariantList &posCmds, QStringList &extData) {
  if (node->getName() == "add") {
    // TODO: Implement adding an agent.    
  }

  else if (node->getName() == "remove") {
    // TODO: Implement removing an agent.    
  }

  else if (node->getName() == "list") {
    // TODO: Implement listing the agents.
  }    
}
