#include <QDebug>
#include <QRegExp>

#include "CommandOption.h"
#include "CommandExecuter.h"
#include "CommandTreeNode.h"
#include "PositionalCommand.h"

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

  int pos = ++lastToken, optMisses = 0;
  QString token;
  for (; pos < tokens.size(); pos++) {
    token = tokens[pos];

    // Option?
    QStringList optToks;
    if (parseOption(token, optToks)) {
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
              if (!checkType(optToks[1], option->getType(), var)) {
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
              if (!checkType(tokens[pos + 1], option->getType(), var)) {
                qWarning() << "Invalid input type for option" << token;
                return false;
              }

              options[option->getLongName()] = var;
              pos++;
            }
          }

          continue;
        }
      }
    }
    else {
      optMisses++;
    }
  }

  int posOffset = (pos - optMisses);

  // Positional command?
  PositionalCommandList posCmdList = node->getPosCmds();
  int posMatched = 0;
  for (int j = 0; j < posCmdList.size() && (j + posOffset) < tokens.size(); j++) {
    token = tokens[j + posOffset];
    PositionalCommand *cmd = posCmdList[j];
    
    QVariant var;
    if (!checkType(token, cmd->getType(), var)) {
      qWarning() << "Invalid type for positional command" << posCmdList[j]->getName();
      return false;
    }

    posCmds.append(var);
    posMatched++;    
  }

  if (posMatched != posCmdList.size()) {
    qWarning() << "Positional command" << posCmdList[posMatched]->getName() << "required";
    return false;
  }

  // Extraneous data?
  for (int h = posOffset + posMatched; h < tokens.size(); h++) {
    extData.append(tokens[h]);
  }

  node->execute(options, posCmds, extData);
  return true;
}

QStringList CommandExecuter::parse(const QString &input) {
  // Parse tokens and account for string literals (single and double
  // quotes) around tokens spanned by white space, for instance.
  QRegExp exp("(?:(?:\")(.+)(?:\")|(?:\')(.+)(?:\'))");
  exp.setMinimal(true);

  QStringList tokens;
  int pos = 0, oldPos = 0;
  while ((pos = exp.indexIn(input, pos)) != -1) {
    QString tok = exp.capturedTexts()[1];
    if (tok.isEmpty()) {
      tok = exp.capturedTexts()[2];
    }
    
    tokens.append(input.mid(oldPos, pos - oldPos).split(" ", QString::SkipEmptyParts));
    tokens.append(tok);
    pos += exp.matchedLength();
    oldPos = pos;    
  }

  // Split any leftovers normally.
  if (oldPos < input.size()) {
    tokens.append(input.mid(oldPos).split(" ", QString::SkipEmptyParts));    
  }

  return tokens;
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
  if (token.isEmpty()) {
    return false;
  }

  if (token.startsWith("--")) {
    // TODO: check first char after -- isn't another -
    
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
    // TODO: check first char after - isn't another -
    
    token = token.mid(1);
    optToks.append(token);
    return true;
  }

  return false;
}

bool CommandExecuter::checkType(const QString &token, CommandType type, QVariant &var) {
  QString lowTok = token.toLower();
  bool ok;
  
  switch (type) {
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
