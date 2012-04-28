#ifndef COMMAND_TREE_NODE_H
#define COMMAND_TREE_NODE_H

#include <QList>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariantMap>
#include <QVariantList>

namespace cmd {
  class CommandOption;
  class CommandFunction;
  class CommandTreeNode;
  class PositionalCommand;

  typedef QList<CommandTreeNode*> CommandTreeNodeList;
  typedef QList<CommandOption*> CommandOptionList;
  typedef QList<PositionalCommand*> PositionalCommandList;

  /**
   * Provides a way to represent a command structure with commands and
   * sub commands with associated options (long/short and w/o inputs)
   * and positional commands.
   */
  class CommandTreeNode {
  public:
    CommandTreeNode(const QString &name = QString(), CommandFunction *func = NULL);
    CommandTreeNode(const QString &name, const QString &shortName, CommandFunction *func = NULL);    
    virtual ~CommandTreeNode();

    QString getName() const { return name; }
    QString getShortName() const { return shortName; }    

    void setDescription(const QString &desc) { this->desc = desc; }
    QString getDescription() const { return desc; }
    bool hasDescription() const { return !desc.isEmpty(); }

    void addNode(CommandTreeNode *node);
    CommandTreeNodeList getNodes() const { return nodes; }

    void addOption(CommandOption *option);
    CommandOptionList getOptions() const { return options; }

    void addPosCmd(PositionalCommand *posCmd);
    PositionalCommandList getPosCmds() const { return posCmds; }

    void print(QDebug dbg = QDebug(QtDebugMsg), int depth = 0) const;

    bool hasFunction() const { return func != NULL; }
    void execute(QVariantMap &options, QVariantList &posCmds, QStringList &extData) const;

    bool isSane() const;

  private:
    QString name, shortName, desc;
    CommandFunction *func;
    CommandTreeNodeList nodes;
    CommandOptionList options;
    PositionalCommandList posCmds;
  };

  inline QDebug operator<<(QDebug debug, const CommandTreeNode &node) {
    node.print(debug);
    return debug;
  }

  inline QDebug operator<<(QDebug debug, const CommandTreeNode *node) {
    node->print(debug);
    return debug;
  }
}

#endif // COMMAND_TREE_NODE_H
