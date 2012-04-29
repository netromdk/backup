#include <QDebug>

#include "cmd/CommandOption.h"
#include "cmd/PositionalCommand.h"

#include "HelpContext.h"
#include "AgentContext.h"
#include "CommandBuilder.h"

CommandBuilder::CommandBuilder() : tree(NULL), helpCtx(NULL), agentCtx(NULL) {
  build();
}

CommandBuilder::~CommandBuilder() {
  if (tree) {
    delete tree;
  }

  if (helpCtx) {
    delete helpCtx;
  }

  if (agentCtx) {
    delete agentCtx;
  }  
}

void CommandBuilder::build() {
  tree = new CommandTreeNode;

  // Help
  helpCtx = new HelpContext(tree);
  
  CommandTreeNode *help = new CommandTreeNode("help", "h", helpCtx);
  help->setPosCmdsOptional(true);
  help->addPosCmd(new PositionalCommand("subcmd", cmd::String));
  tree->addNode(help);

  // Agent management
  agentCtx = new AgentContext;
  
  CommandTreeNode *agentMgt = new CommandTreeNode("agents", "a");
  tree->addNode(agentMgt);

  CommandTreeNode *agentAdd = new CommandTreeNode("add", "a", agentCtx);
  agentAdd->setPosCmdsOptional(true);
  agentAdd->addPosCmd(new PositionalCommand("id", cmd::String));
  agentMgt->addNode(agentAdd);

  CommandTreeNode *agentRem = new CommandTreeNode("remove", "r", agentCtx);
  agentRem->setPosCmdsOptional(true);
  agentRem->addPosCmd(new PositionalCommand("id", cmd::String));
  agentRem->addOption(new CommandOption("all", "a"));
  agentRem->addOption(new CommandOption("force", "f"));  
  agentMgt->addNode(agentRem);

  CommandTreeNode *agentList = new CommandTreeNode("list", "l", agentCtx);
  agentList->setPosCmdsOptional(true);
  agentList->addPosCmd(new PositionalCommand("id", cmd::String));  
  agentMgt->addNode(agentList);  
}
