#include "CommandOption.h"

CommandOption::CommandOption(const QString &longName, const QString &shortName,
                             CommandType type, bool inputOptional)
  : longName(longName), shortName(shortName), type(type),
    inputOptional(inputOptional)
{ }
