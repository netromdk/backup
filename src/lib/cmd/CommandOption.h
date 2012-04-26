#ifndef COMMAND_OPTION_H
#define COMMAND_OPTION_H

#include <QMap>
#include <QString>
#include <QVariant>

#include "CommandType.h"

namespace cmd {
  /**
   * Provides a command option which has a long name (--example) and an
   * optional short name (-e). An option can also have a value
   * associated with it, for long names it would look like
   * "--longname=value" and for short names it would be "-shortname
   * value". This value can be made optional.
   */
  class CommandOption {
  public:
    /**
     * Constructs an option with a long name and an optional short name
     * and input type. If an input type is specified it can be made
     * optional by setting 'inputOptional'.
     */ 
    CommandOption(const QString &longName, const QString &shortName = QString(),
                  CommandType type = NoType, bool inputOptional = false);

    QString getLongName() const { return longName; }
  
    QString getShortName() const { return shortName; }
    bool hasShortName() const { return !shortName.isEmpty(); }
  
    CommandType getType() const { return type; }
    bool takesInput() const { return type != NoType; }
    bool isInputOptional() const { return inputOptional; }

    void setDescription(const QString &desc) { this->desc = desc; }
    QString getDescription() const { return desc; }
    bool hasDescription() const { return !desc.isEmpty(); }

  private:
    QString longName, shortName, desc;
    CommandType type;
    bool inputOptional;
  };
}

#endif // COMMAND_OPTION_H
