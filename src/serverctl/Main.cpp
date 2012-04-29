#include <QDebug>
#include <QCoreApplication>

#include "cmd/CommandConsole.h"
#include "cmd/CommandTreeNode.h"
using namespace cmd;

#include "util/Utility.h"

#include "srv/ServerManager.h"

#include "CommandBuilder.h"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  srv::ServerManager mgr;
  if (!mgr.isValid()) {
    qWarning() << "Could not initialize connection to local server database.";
    return -1;
  }

  CommandBuilder builder;

  const CommandTreeNode *tree = builder.getRootNode();
  if (!tree->isSane()) {
    qWarning() << "Tree is not sane.";
    return -1;
  }

  CommandConsole console(tree);
  if (argc > 1) {
    console.execute(util::Utility::argsToList(argc, argv).join(" "));
  }
  else {
    console.loop();
  }

  return 0;
}
