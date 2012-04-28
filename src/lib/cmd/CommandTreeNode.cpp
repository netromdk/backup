#include <QtAlgorithms>

#include "CommandOption.h"
#include "CommandTreeNode.h"
#include "CommandFunction.h"
#include "PositionalCommand.h"

namespace cmd {
  CommandTreeNode::CommandTreeNode(const QString &name, CommandFunction *func)
    : name(name), func(func)
  { }

  CommandTreeNode::CommandTreeNode(const QString &name, const QString &shortName,
                                   CommandFunction *func)
    : name(name), shortName(shortName), func(func)
  { }  

  CommandTreeNode::~CommandTreeNode() {
    qDeleteAll(nodes);
  }

  void CommandTreeNode::addNode(CommandTreeNode *node) {
    nodes.append(node);
  }

  void CommandTreeNode::addOption(CommandOption *option) {
    options.append(option);
  }

  void CommandTreeNode::addPosCmd(PositionalCommand *posCmd) {
    posCmds.append(posCmd);
  }

  void CommandTreeNode::print(QDebug dbg, int depth) const {
    QString pad = "";
    for (int i = 0; i < depth; i++) {
      pad += "  ";
    }

    // Name / short name.
    QString n = (name.isEmpty() ? "<no name>" : name);
    if (!shortName.isEmpty()) {
      n += " | " + shortName;
    }
    dbg.nospace() << qPrintable(pad) << qPrintable(n);

    // Description
    if (hasDescription()) {
      dbg.nospace() << " # " << qPrintable(desc);
    }

    dbg << "\n";

    // Options
    pad += "  ";
    foreach (CommandOption *option, options) {
      dbg.nospace() << qPrintable(pad) << "--" << qPrintable(option->getLongName());
      const char *typ = NULL;
      if (option->takesInput()) {
        typ = QVariant::typeToName((QVariant::Type) option->getType());
        if (option->isInputOptional()) {
          dbg.nospace() << "(";
        }
        dbg.nospace() << "=<" << typ << ">";
        if (option->isInputOptional()) {
          dbg.nospace() << ")";
        }      
      }
      if (option->hasShortName()) {
        dbg.nospace() << " | " << "-" << qPrintable(option->getShortName());
        if (typ) {
          dbg.nospace() << " ";
          if (option->isInputOptional()) {
            dbg.nospace() << "(";
          }
          dbg.nospace() << "<" << typ << ">";
          if (option->isInputOptional()) {
            dbg.nospace() << ")";
          }        
        }
      }
      if (option->hasDescription()) {
        dbg.nospace() << " # " << qPrintable(option->getDescription());
      }
      dbg << "\n";
    }

    // Positional commands
    foreach (PositionalCommand *cmd, posCmds) {
      dbg.nospace() << qPrintable(pad) << "<" << qPrintable(cmd->getName()) << ">"
                    << " (" << QVariant::typeToName((QVariant::Type) cmd->getType())
                    << " type)";
      if (cmd->hasDescription()) {
        dbg.nospace() << " # " << qPrintable(cmd->getDescription());
      }
      dbg << "\n";
    }

    // Nodes
    depth++;
    foreach (CommandTreeNode *node, nodes) {
      node->print(dbg, depth);
    }
  }

  void CommandTreeNode::execute(QVariantMap &options, QVariantList &posCmds,
                                QStringList &extData) const {
    if (hasFunction()) {
      func->execute(this, options, posCmds, extData);
    }
    else {
      qWarning() << getName() << "has no defined function.";
    }
  }

  bool CommandTreeNode::isSane() const {
    foreach (const CommandOption *opt, options) {
      if (opt->getLongName().isEmpty()) {
        qWarning() << "Missing option long name\n";
        qWarning() << this;
        return false;
      }
      
      foreach (const CommandOption *opt2, options) {
        if (opt == opt2) continue;

        if (opt->getLongName() == opt2->getLongName()) {
          qWarning() << "Duplicate option long name:" << opt->getLongName() << "\n";
          qWarning() << this;
          return false;
        }

        else if (!opt->getShortName().isEmpty() && !opt2->getShortName().isEmpty()
                 && opt->getShortName() == opt2->getShortName()) {
          qWarning() << "Duplicate option short name:" << opt->getShortName() << "\n";
          qWarning() << this;
          return false;
        }        
      }      
    }

    foreach (const PositionalCommand *pos, posCmds) {
      if (pos->getName().isEmpty()) {
        qWarning() << "Missing positional command name\n";
        qWarning() << this;
        return false;
      }

      foreach (const PositionalCommand *pos2, posCmds) {
        if (pos == pos2) continue;

        if (pos->getName() == pos2->getName()) {
          qWarning() << "Duplicate positional command name:" << pos->getName() << "\n";
          qWarning() << this;
          return false;
        }
      }      
    }
    
    foreach (const CommandTreeNode *n, nodes) {
      if (n->getName().isEmpty()) {
        qWarning() << "Missing command name\n";
        qWarning() << this;
        return false;
      }
      
      foreach (const CommandTreeNode *n2, nodes) {
        if (n == n2) continue;

        if (n->getName() == n2->getName()) {
          qWarning() << "Duplicate command name:" << n->getName() << "\n";
          qWarning() << n;
          qWarning() << n2;          
          return false;
        }

        else if (!n->getShortName().isEmpty() && !n2->getShortName().isEmpty()
                 && n->getShortName() == n2->getShortName()) {
          qWarning() << "Duplicate command short name:" << n->getShortName() << "\n";
          qWarning() << n;
          qWarning() << n2;          
          return false;          
        }        
      }
      
      if (!n->isSane()) return false;      
    }

    return true;
  }
}
