#include <QSet>
#include <QStringList>

#include "ConfigPathElement.h"

const QRegExp ConfigPathElementQuantifier::regexp =
  QRegExp("\\[\\s*("
          "(\\d+)"
          "|"
          "(\\d+\\s*\\-\\s*\\d+)"
          "|"
          "("
             "\\s*((\\d+)|(\\d+\\s*\\-\\s*\\d+)){1}"
             "(\\s*\\,\\s*((\\d+)|(\\d+\\s*\\-\\s*\\d+))\\s*)*"
          ")"
          "|"
          "(\\*)"          
          ")\\s*\\]");

ConfigPathElementQuantifier::ConfigPathElementQuantifier(const QString &quantifier)
  : ConfigPathElement(Quantifier), quantifier(quantifier), kleene(false)
{
  parse();
}

void ConfigPathElementQuantifier::parse() {
  indices.clear();
  
  if (!regexp.exactMatch(quantifier)) {
    return;
  }
  
  QString q = quantifier.mid(1, quantifier.size() - 2);
  QStringList elms = q.split(",", QString::SkipEmptyParts);

  if (elms.size() == 1 && elms[0].trimmed() == "*") {
    kleene = true;
    return;
  }

  bool fail = false, ok, ok2;
  int index, index2;
  foreach (const QString &elm, elms) {
    // Range.
    if (elm.contains("-")) {
      QStringList subelms = elm.split("-", QString::SkipEmptyParts);
      if (subelms.size() == 2) {
        index = subelms[0].toInt(&ok);
        index2 = subelms[1].toInt(&ok2);      
        if (!ok || !ok2) {
          fail = true;
          break;
        }

        if (index > index2) {
          fail = true;
          break;
        }

        for (int i = index; i <= index2; i++) {
          indices.append(i);
        }
      }

      continue;      
    }

    // Index.
    index = elm.toInt(&ok);
    if (!ok) {
      fail = true;
      break;
    }

    indices.append(index);
  }

  if (fail) {
    indices.clear();
    return;
  }

  indices = indices.toSet().toList();
}
