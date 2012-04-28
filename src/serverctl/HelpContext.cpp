#include <QDebug>

#include "HelpContext.h"

HelpContext::HelpContext(const CommandTreeNode *tree) : tree(tree) { }

void HelpContext::execute(const CommandTreeNode *node, QVariantMap &options,
                          QVariantList &posCmds, QStringList &extData) {
  if (posCmds.size() == 0) {
    qDebug() << tree;
    return;
  }

  QString cmd = posCmds[0].toString();
  CommandTreeNode *n = tree->getNode(cmd);
  if (n) {
    qDebug() << n;
  }
  else {
    qWarning() << "No help for unknown command" << cmd;
  }
}
