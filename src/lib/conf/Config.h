#ifndef CONFIG_H
#define CONFIG_H

#include <QFlags>
#include <QString>

#include "ConfigTreeNode.h"

class QXmlStreamWriter;

/**
 * Reads and writes configuration files in XML format.
 */
class Config {
public:
  enum Error {
    NoError = 0x0,
    NoPathDefined,
    PathNonExistent,
    PathNonReadable,
    PathNonWritable,
    SyntaxError
  };
  Q_DECLARE_FLAGS(Errors, Error);

  Config();  
  Config(const QString &path);

  void setPath(const QString &path);
  QString getPath() const { return path; }
  
  bool isValid();
  Errors getErrors() const { return errors; }
  
  ConfigTreeNode *parse();
  bool commit(const ConfigTreeNode *tree);

private:
  void init();
  void resetErrors() { errors = NoError; }
  void writeTree(const ConfigTreeNode *node, QXmlStreamWriter &writer, bool skip = false);  
  
  QString path;
  Errors errors;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Config::Errors);

#endif // CONFIG_H
