#include "CommandOption.h"

CommandOption::CommandOption(const QString &longName, const QString &shortName,
                             Type type)
  : longName(longName), shortName(shortName), type(type)
{ }
