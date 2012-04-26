#ifndef COMMAND_CONSOLE_H
#define COMMAND_CONSOLE_H

#include <QString>

class CommandTreeNode;
class CommandExecuter;

/**
 * Provides a console loop asking for commands and interpreting them
 * according to the command tree given.
 */
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
   *
   * The supported substitutional variables are:
   * <table border=0 cellpadding=5>
   * <tr><td>u</td><td>Yields the user name of the current user.</td></tr>
   * <tr><td>yyyy</td><td>Yields the current year with four digits (e.g. 2012).</td></tr>
   * <tr><td>yy</td><td>Yields the current year with two digits (e.g. 12).</td></tr>
   * <tr><td>MMMM</td><td>Yields the current month in the longest form (e.g. April).</td></tr>
   * <tr><td>MMM</td><td>Yields the current month in long form (e.g. Apr).</td></tr>
   * <tr><td>MM</td><td>Yields the current month as a number with leading zeroes (e.g. 04).</td></tr>
   * <tr><td>M</td><td>Yields the current month as a number without leading zeroes (e.g. 4).</td></tr>
   * <tr><td>dddd</td><td>Yields the current day in the longest form (e.g. Thursday).</td></tr>
   * <tr><td>ddd</td><td>Yields the current day in long form (e.g. Thu).</td></tr>
   * <tr><td>dd</td><td>Yields the current day as a number with leading zeroes (e.g. 03).</td></tr>
   * <tr><td>d</td><td>Yields the current day as a number without leading zeroes (e.g. 3).</td></tr>
   * <tr><td>hh</td><td>Yields the current hour as a number with leading zeroes (e.g. 09).</td></tr>
   * <tr><td>h</td><td>Yields the current hour as a number without leading zeroes (e.g. 9).</td></tr>
   * <tr><td>mm</td><td>Yields the current minute as a number with leading zeroes (e.g. 06).</td></tr> 
   * <tr><td>m</td><td>Yields the current minute as a number without leading zeroes (e.g. 6).</td></tr>
   * <tr><td>ss</td><td>Yields the current second as a number with leading zeroes (e.g. 01).</td></tr> 
   * <tr><td>s</td><td>Yields the current second as a number without leading zeroes (e.g. 1).</td></tr>
   * <tr><td>AP</td><td>Yields either "PM" or "AM".</td></tr>
   * <tr><td>ap</td><td>Yields either "pm" or "am".</td></tr>   
   * </table>
   *
   * Use with "%" before them, e.g. "%MMM". <b>Note that all values
   * follow the system locale.</b>
   */
  void setTermString(const QString &term);
  
  QString getTermString() const { return termString; }  

private:
  QString resolveTerm();
  
  CommandExecuter *executer;
  QString termString;
};

#endif // COMMAND_CONSOLE_H
