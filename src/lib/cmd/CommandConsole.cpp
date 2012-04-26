#include <QDateTime>

#include "util/Utility.h"
#include "CommandConsole.h"
#include "CommandExecuter.h"
#include "CommandTreeNode.h"

namespace cmd {
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
    QString term = termString.replace("%u", util::Utility::getUserName());

    QDateTime now = QDateTime::currentDateTime(); 
    term = term.replace("%yyyy", now.toString("yyyy")); 
    term = term.replace("%yy", now.toString("yy"));
    term = term.replace("%MMMM", now.toString("MMMM"));    
    term = term.replace("%MMM", now.toString("MMM"));  
    term = term.replace("%MM", now.toString("MM"));
    term = term.replace("%M", now.toString("M"));
    term = term.replace("%dddd", now.toString("dddd"));    
    term = term.replace("%ddd", now.toString("ddd"));  
    term = term.replace("%dd", now.toString("dd"));
    term = term.replace("%d", now.toString("d"));     
    term = term.replace("%hh", now.toString("hh"));
    term = term.replace("%h", now.toString("h"));   
    term = term.replace("%mm", now.toString("mm"));
    term = term.replace("%m", now.toString("m"));   
    term = term.replace("%ss", now.toString("ss"));
    term = term.replace("%s", now.toString("s"));   
    term = term.replace("%AP", now.toString("AP")); 
    term = term.replace("%ap", now.toString("ap")); 

    return term;
  }
}
