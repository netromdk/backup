#include <QDebug>
#include <QCoreApplication>

#include "cmd/CommandConsole.h"
#include "cmd/CommandTreeNode.h"
using namespace cmd;

#include "util/Utility.h"

#include "CommandBuilder.h"

int main(int argc, char **argv) {
  QCoreApplication app(argc, argv);

  CommandBuilder builder;
  CommandConsole console(builder.getRootNode());
  
  if (argc > 1) {
    console.execute(util::Utility::argsToList(argc, argv).join(" "));
  }
  else {
    console.loop();
  }

  return 0;
}
