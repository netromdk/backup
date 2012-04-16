#ifndef CONFIG_PATH_ELEMENT_H
#define CONFIG_PATH_ELEMENT_H

#include <QList>
#include <QString>

class ConfigPathElement;
typedef QList<ConfigPathElement*> ConfigPathList;

class ConfigPathElement {
public:
  enum Kind {
    Name,    
    Quantifier
  };

  virtual ~ConfigPathElement() { }

  Kind getKind() const { return kind; }

  virtual QString toString() const = 0;
  
protected:
  ConfigPathElement(Kind kind) : kind(kind) { }

private:
  Kind kind;
};

class ConfigPathElementName : public ConfigPathElement {
public:
  ConfigPathElementName(const QString &name)
    : ConfigPathElement(Name), name(name) { }

  virtual QString toString() const { return name; }
  QString getName() const { return name; }

private:
  QString name;
};

class ConfigPathElementQuantifier : public ConfigPathElement {

};

#endif // CONFIG_PATH_ELEMENT_H
