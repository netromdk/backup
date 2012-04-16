#ifndef CONFIG_H
#define CONFIG_H

#include <QFlags>
#include <QString>

class ConfigTreeNode;

/**
 * Reads and writes configuration files in XML format.
 */
class Config {
public:
  enum Error {
    NoError = 0x0,
    NoPathDefined = 0x1,
    PathNonExistent = 0x2,
    PathNonReadable = 0x4,
    PathNonWritable = 0x8,
    SyntaxError = 0x16
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
  
  QString path;
  Errors errors;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Config::Errors);

#endif // CONFIG_H
