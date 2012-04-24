#ifndef COMMAND_OPTION_H
#define COMMAND_OPTION_H

#include <QMap>
#include <QString>
#include <QVariant>

typedef QMap<QString, QVariant> OptionMap;

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
   * Supported option types for input.
   */ 
  enum Type {
    NoType = 0,
    Bool = QVariant::Bool,
    Char = QVariant::Char,
    Double = QVariant::Double,
    Int = QVariant::Int, 
    UInt = QVariant::UInt,    
    LongLong = QVariant::LongLong,
    ULongLong = QVariant::ULongLong,
    String = QVariant::String
  };

  /**
   * Constructs an option with a long name and an optional short name
   * and input type.
   */ 
  CommandOption(const QString &longName, const QString &shortName = QString(),
                Type type = NoType);

  QString getLongName() const { return longName; }
  
  QString getShortName() const { return shortName; }
  bool hasShortName() const { return !shortName.isEmpty(); }
  
  Type getType() const { return type; }
  bool requiresInput() const { return type != NoType; }  

private:
  QString longName, shortName;
  Type type;
};

#endif // COMMAND_OPTION_H
