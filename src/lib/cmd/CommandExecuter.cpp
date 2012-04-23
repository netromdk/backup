#include <QDebug>

#include "CommandExecuter.h"
#include "CommandTreeNode.h"

CommandExecuter::CommandExecuter(CommandTreeNode *tree) : tree(tree) {
  
}

bool CommandExecuter::execute(const QString &input) {
  clearState();

  qDebug() << "input:" << input;
  
  // TODO: Error handling about parsing (like missing string
  // literals).
  QStringList tokens = parse(input);
  qDebug() << "tokens:" << tokens;

  return traverse(tree, tokens);
}

QStringList CommandExecuter::parse(const QString &input) {
  // TODO: Improve this one!!
  return input.split(" ");
}

void CommandExecuter::clearState() {
  options.clear();
  posCmds.clear();
  extData.clear();
}

bool CommandExecuter::traverse(CommandTreeNode *node, QStringList &tokens,
                               uint pos, bool done) {
  if (done) {
    node->execute(options, posCmds, extData);
    clearState();
    return true;
  }
  
  if (pos >= tokens.size()) {
    return false;
  }

  QString token = tokens[pos];
  qDebug() << "->" << token;

  pos++;

  CommandTreeNodeList nodes;
  if (!node->getName().isEmpty()) {
    nodes.append(node);
  }
  nodes.append(node->getNodes());      
  
  foreach (CommandTreeNode *n, nodes) {
    // Is it a command?
    if (n->getName() == token) {
      return traverse(n, tokens, pos, pos >= tokens.size());
    }

    // Option?

    // Positional Command?
  }

  qWarning() << "Not valid token" << token;
  return false;
}
