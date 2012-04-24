#include "CommandOption.h"

CommandOption::CommandOption(const QString &longName, const QString &shortName,
                             CommandType type)
  : longName(longName), shortName(shortName), type(type)
{ }
