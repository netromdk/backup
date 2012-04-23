#ifndef COMMAND_FUNCTION_H
#define COMMAND_FUNCTION_H

#include <QStringList>

#include "CommandOption.h"

class CommandTreeNode;

/**
 * Provides an abstract class that encapsulates what should be done
 * when a command has been parsed successfully.
 */
class CommandFunction {
public:
  virtual ~CommandFunction() { }
  
  /**
   * Execute is called on success. The node will point to the last sub
   * command of the input.
   */
  virtual void execute(CommandTreeNode *node, OptionMap &options,
                       QStringList &posCmds, QStringList &extData) = 0;
};

#endif // COMMAND_FUNCTION_H
