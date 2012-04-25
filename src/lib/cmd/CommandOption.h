#ifndef COMMAND_OPTION_H
#define COMMAND_OPTION_H

#include <QMap>
#include <QString>
#include <QVariant>

#include "CommandType.h"

/**
 * Provides a command option which has a long name (--example) and an
 * optional short name (-e). An option can also have a value
 * associated with it, for long names it would look like
 * "--longname=value" and for short names it would be "-shortname
 * value".
 */
class CommandOption {
public:
  /**
   * Constructs an option with a long name and an optional short name
   * and input type.
   */ 
  CommandOption(const QString &longName, const QString &shortName = QString(),
                CommandType type = NoType);

  QString getLongName() const { return longName; }
  
  QString getShortName() const { return shortName; }
  bool hasShortName() const { return !shortName.isEmpty(); }
  
  CommandType getType() const { return type; }
  bool requiresInput() const { return type != NoType; }

  void setDescription(const QString &desc) { this->desc = desc; }
  QString getDescription() const { return desc; }
  bool hasDescription() const { return !desc.isEmpty(); }

private:
  QString longName, shortName, desc;
  CommandType type;
};

#endif // COMMAND_OPTION_H
