#include <QStack>
#include <QDebug>
#include <QFileInfo>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "Config.h"
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

ConfigTreeNode *Config::parse() {
  resetErrors();
  
  QFile file(path);
  if (!file.open(QIODevice::ReadOnly)) {
    errors |= PathNonReadable;
    return NULL;
  }

  QStack<ConfigTreeNode*> levels;
  ConfigTreeNode *root = new ConfigTreeNode("root");
  bool first = true;
  QString comment;
  
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

      // Save comment.
      if (!comment.isEmpty()) {
        node->setComment(comment);
        comment = "";
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

    if (token == QXmlStreamReader::Comment) {
      comment = reader.text().toString();
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
    delete root;
    return NULL;
  }
  
  return root;
}

bool Config::commit(const ConfigTreeNode *tree) {
  resetErrors();
  
  QFile file(path);
  if (!file.open(QIODevice::WriteOnly)) {
    errors |= PathNonWritable;
    return false;
  }

  QXmlStreamWriter writer(&file);
  writer.setAutoFormatting(true);
  writer.setAutoFormattingIndent(2);
  writer.writeStartDocument();

  // Skip writing first root element.
  writeTree(tree, writer, true);

  writer.writeEndDocument();
  file.flush();
  file.close();
  
  return true;
}

void Config::init() {
  resetErrors();
}

void Config::writeTree(const ConfigTreeNode *node, QXmlStreamWriter &writer, bool skip) {
  if (!skip) {
    if (node->hasComment()) {
      writer.writeComment(node->getComment());
    }
    
    writer.writeStartElement(node->getName());

    const QVariantList &values = node->getValues();
    foreach (const QVariant &value, values) {
      switch (value.type()) {
      // Maps are considered attributes.
      case QMetaType::QVariantMap: {
        QVariantMap map = value.toMap();
        foreach (const QString &key, map.keys()) {
          const QVariant &var = map[key];
          writer.writeAttribute(key, var.toString());
        }
        break;
      }

      default:
        // Only write out if the node is a leaf.
        if (node->getNodes().size() == 0) {
          writer.writeCharacters(value.toString());
        }
        break;
      }
    }
  }
  
  foreach (ConfigTreeNode *elm, node->getNodes()) {
    writeTree(elm, writer, false);
  }

  if (!skip) {
    writer.writeEndElement();
  }
}
