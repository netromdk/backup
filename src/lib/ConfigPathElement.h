#ifndef CONFIG_PATH_ELEMENT_H
#define CONFIG_PATH_ELEMENT_H

#include <QList>
#include <QRegExp>
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


/**
 * The quantifier can be an index, an index range (like "1-2"), a
 * colon-separated list of indices and ranges, or the Kleene start (to
 * select all).
 */
class ConfigPathElementQuantifier : public ConfigPathElement {
public:
  ConfigPathElementQuantifier(const QString &quantifier);
  
  /**
   * The regular expression that matches a quantifier. 
   */
  static const QRegExp regexp;

  virtual QString toString() const { return quantifier; }
  bool isKleene() const { return kleene; }
  QList<int> getIndices() const { return indices; }

private:
  void parse();
  
  QString quantifier;
  bool kleene;
  QList<int> indices;
};

#endif // CONFIG_PATH_ELEMENT_H
