#include "CommandConsole.h"
#include "CommandExecuter.h"
#include "CommandTreeNode.h"

CommandConsole::CommandConsole(const CommandTreeNode *tree) : termString("> ") {
  executer = new CommandExecuter(tree);
}

CommandConsole::~CommandConsole() {
  if (executer) {
    delete executer;
  }
}

void CommandConsole::loop() {
  QTextStream stdIn(stdin, QIODevice::ReadOnly),
    stdOut(stdout, QIODevice::WriteOnly);
  
  stdIn.setCodec("UTF-8");
  stdIn.setAutoDetectUnicode(true);
  
  QString line;
  
  forever {
    stdOut << resolveTerm();
    stdOut.flush();

    line = stdIn.readLine();

    // Check for EOF.
    if (line.isNull()) {
      qDebug() << "Bye bye..";
      break;
    }
    
    if (line.isEmpty()) continue;
    
    executer->execute(line);
  }
}

void CommandConsole::setTermString(const QString &term) {
  termString = term;
}

QString CommandConsole::resolveTerm() {
  return termString;
}
