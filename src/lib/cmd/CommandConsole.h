#ifndef COMMAND_CONSOLE_H
#define COMMAND_CONSOLE_H

#include <QString>

class CommandTreeNode;
class CommandExecuter;

class CommandConsole {
public:
  CommandConsole(const CommandTreeNode *tree);
  virtual ~CommandConsole();

  /**
   * Initiate a console loop for processing commands.
   */
  void loop();

  /**
   * Sets the terminal string which appears before every command
   * prompt.
   */
  void setTermString(const QString &term);
  QString getTermString() const { return termString; }  

private:
  QString resolveTerm();
  
  CommandExecuter *executer;
  QString termString;
};

#endif // COMMAND_CONSOLE_H
