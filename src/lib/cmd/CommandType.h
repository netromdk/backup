#ifndef COMMAND_TYPE_H
#define COMMAND_TYPE_H

#include <QVariant>

namespace cmd {
  /**
   * Supported command/option types for input.
   */ 
  enum CommandType {
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
}

#endif // COMMAND_TYPE_H
