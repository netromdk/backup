#include <QStack>
#include <QDebug>
#include <QFileInfo>
#include <QXmlStreamReader>

#include "Config.h"
#include "ConfigTree.h"
#include "ConfigTreeNode.h"

Config::Config() {
  init();
}

Config::Config(const QString &path) : path(path) {
  init();
}

void Config::setPath(const QString &path) {
  this->path = path;
}

bool Config::isValid() {
  resetErrors();
  
  if (path.isEmpty()) {
    errors |= NoPathDefined;
    return false;
  }

  QFileInfo info(path);
  if (!info.exists()) {
    errors |= PathNonExistent;    
    return false;
  }

  bool fail = false;
  if (!info.isReadable()) {
    errors |= PathNonReadable;
    fail = true;
  }
  if (!info.isWritable()) {
    errors |= PathNonWritable;
    fail = true;    
  }  

  if (fail) return false;

  return true;
}

bool Config::parse(ConfigTree &tree) {
  resetErrors();
  
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    errors |= PathNonReadable;
    return false;
  }

  QStack<ConfigTreeNode*> levels;
  ConfigTreeNode *root = tree.getRoot();
  bool first = true;
  
  QXmlStreamReader reader(&file);
  while (!reader.atEnd() && !reader.hasError()) {
    QXmlStreamReader::TokenType token = reader.readNext();
    if (token == QXmlStreamReader::StartDocument) {
      continue;
    }

    if (token == QXmlStreamReader::StartElement) {
      ConfigTreeNode *node = new ConfigTreeNode(reader.name().toString());
      levels.push(node);

      // Save map of attributes.
      QVariantMap atts;
      foreach (const QXmlStreamAttribute &att, reader.attributes()) {
        atts[att.name().toString()] = att.value().toString();
      }
      if (atts.size() > 0) {
        node->addValue(atts);
      }

      if (first) {
        first = false;
        root->addNode(node);
      }
    }

    if (token == QXmlStreamReader::Characters) {
      if (levels.isEmpty()) continue;
      ConfigTreeNode *node = levels.top();

      // Save element text.
      QString text = reader.text().toString().trimmed();
      if (!text.isEmpty()) {
        node->addValue(text);
      }
    }

    else if (token == QXmlStreamReader::EndElement) {
      ConfigTreeNode *node = levels.pop();
      if (levels.isEmpty()) {
        continue;
      }
      
      ConfigTreeNode *parent = levels.top();
      parent->addNode(node);
    }    
  }

  if (reader.hasError()) {
    qCritical() << "parse error:" << reader.errorString();
    errors |= SyntaxError;
    return false;
  }
  
  return true;
}

bool Config::commit(const ConfigTree &tree) {
  return true;
}

void Config::init() {
  resetErrors();
}
