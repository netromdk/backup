#ifndef COMMAND_FUNCTION_H
#define COMMAND_FUNCTION_H

#include <QStringList>
#include <QVariantMap>
#include <QVariantList>

namespace cmd {
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
    virtual void execute(const CommandTreeNode *node, QVariantMap &options,
                         QVariantList &posCmds, QStringList &extData) = 0;
  };
}

#endif // COMMAND_FUNCTION_H
