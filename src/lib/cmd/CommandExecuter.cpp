#include <QDebug>

#include "CommandExecuter.h"
#include "CommandTreeNode.h"

CommandExecuter::CommandExecuter(CommandTreeNode *tree) : tree(tree) {
  
}

bool CommandExecuter::execute(const QString &input) {
  clearState();

  qDebug() << "input:" << input;
  
  // TODO: Error handling about parsing (like missing string
  // literals).
  QStringList tokens = parse(input);
  qDebug() << "tokens:" << tokens;

  CommandTreeNode *node = traverse(tree, tokens);
  if (!node) {
    qWarning() << "Invalid command" << tokens[lastToken];
    return false;
  }
  qDebug() << "got sub node:" << node->getName();

  // Check if no further tokens exist.
  if (lastToken == tokens.size() - 1) {
    node->execute(options, posCmds, extData);
    return true;
  }

  int pos = ++lastToken;
  QString token;
  bool match;
  for (; pos < tokens.size(); pos++) {
    token = tokens[pos];
    match = false;

    // Option?
    QStringList optToks;
    if (parseOption(token, optToks)) {
      qDebug() << token << "->" << optToks;
      QString optName = optToks[0];

      foreach (CommandOption *option, node->getOptions()) {
        if (option->getLongName() == optName || option->getShortName() == optName) {
          if (options.keys().contains(option->getLongName())) {
            qWarning() << "Duplicate option" << token;
            return false;
          }

          if (!option->requiresInput()) {
            options[option->getLongName()];
          }
          else {
            QVariant var;
            if (optToks.size() == 2) {
              if (!checkOptionType(optToks[1], option, var)) {
                qWarning() << "Invalid input type for option" << token;
                return false;                
              }

              options[option->getLongName()] = var;
            }
            else if ((pos + 1) >= tokens.size()) {
              qWarning() << "Option" << token << "requires input but none was given.";
              return false;
            }
            else {
              if (!checkOptionType(tokens[pos + 1], option, var)) {
                qWarning() << "Invalid input type for option" << token;
                return false;
              }

              options[option->getLongName()] = var;
              pos++;
            }
          }

          match = true;
          continue;
        }
      }
    }

    // Positional command?
    

    
    if (!match) {
      qWarning() << "Invalid token" << token;
      return false;
    }
  }

  node->execute(options, posCmds, extData);
  return true;
}

QStringList CommandExecuter::parse(const QString &input) {
  // TODO: Improve this one!!
  return input.split(" ");
}

void CommandExecuter::clearState() {
  lastToken = 0;
  options.clear();
  posCmds.clear();
  extData.clear();
}

CommandTreeNode *CommandExecuter::traverse(CommandTreeNode *node,
                                           QStringList &tokens, uint pos) {
  if (pos >= tokens.size()) {
    return node;
  }
  
  QString token = tokens[pos];
  lastToken = pos;

  if (node->getName() == token) {
    return node;
  }

  foreach (CommandTreeNode *n, node->getNodes()) {
    if (n->getName() == token) {
      // If the node has no children then return at once so that the
      // extra tokens can be checked as options etc..
      if (n->getNodes().size() == 0) {
        return n;
      }
      
      return traverse(n, tokens, pos + 1);
    }
  }

  return NULL;
}

bool CommandExecuter::parseOption(QString token, QStringList &optToks) {
  qDebug() << "parse" << token;
  
  if (token.isEmpty()) {
    return false;
  }

  if (token.startsWith("--")) {
    token = token.mid(2);

    // TODO: better parsing.. If it's a string, for instance, using
    // string literals and a = inside...
    QStringList elms = token.split("=", QString::SkipEmptyParts);
    if (elms.size() == 2) {
      optToks.append(elms);
    }
    else {
      optToks.append(elms[0]);
    }

    return true;
  }

  else if (token.startsWith("-")) {
    token = token.mid(1);
    optToks.append(token);
    return true;
  }

  return false;
}

bool CommandExecuter::checkOptionType(const QString &token, CommandOption *option,
                                      QVariant &var) {
  QString lowTok = token.toLower();
  bool ok;
  
  switch (option->getType()) {
  case NoType:
    return false;

  case Bool: 
    if (lowTok != "true" && lowTok != "false") {
      return false;
    }
    var = (lowTok == "true");
    break;

  case Char:
    if (token.size() > 1) {
      return false;
    }
    var = token[0];
    break;

  case Double: 
    var = token.toDouble(&ok);
    if (!ok) return false;
    break;

  case Int: 
    var = token.toInt(&ok);
    if (!ok) return false;
    break;

  case UInt: 
    var = token.toUInt(&ok);
    if (!ok) return false;
    break;

  case LongLong: 
    var = token.toLongLong(&ok);
    if (!ok) return false;
    break;

  case ULongLong: 
    var = token.toULongLong(&ok);
    if (!ok) return false;
    break;

  case String: 
    var = token;
    break;                    
  }
  
  return true;
}
