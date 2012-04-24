#ifndef POSITIONAL_COMMAND_H
#define POSITIONAL_COMMAND_H

#include <QString>

#include "CommandType.h"

class PositionalCommand {
public:
  PositionalCommand(const QString &name, CommandType type);

  QString getName() const { return name; }
  CommandType getType() const { return type; }

private:
  QString name;
  CommandType type;
};

#endif // POSITIONAL_COMMAND_H
