#include "PositionalCommand.h"

namespace cmd {
  PositionalCommand::PositionalCommand(const QString &name, CommandType type)
    : name(name), type(type)
  { }
}
