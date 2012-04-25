#ifndef POSITIONAL_COMMAND_H
#define POSITIONAL_COMMAND_H

#include <QString>

#include "CommandType.h"

class PositionalCommand {
public:
  PositionalCommand(const QString &name, CommandType type);

  QString getName() const { return name; }
  CommandType getType() const { return type; }

  void setDescription(const QString &desc) { this->desc = desc; }
  QString getDescription() const { return desc; }
  bool hasDescription() const { return !desc.isEmpty(); }  

private:
  QString name, desc;
  CommandType type;
};

#endif // POSITIONAL_COMMAND_H
