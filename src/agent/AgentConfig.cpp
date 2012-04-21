#include <QDir>

#include "util/Paths.h"
#include "AgentConfig.h"
#include "DefaultConfig.h"

AgentConfig::AgentConfig() : tree(NULL), valid(false) {
  QDir().mkpath(Paths::getConfigDir());
  config.setPath(Paths::getConfigDir() + "/agent.conf");
  load();

  if (config.getErrors().testFlag(Config::PathNonExistent)) {
    qDebug() << "Config does not exist:" << config.getPath();
    qDebug() << "Writing default.";
    writeDefault();
    if (valid) {
      load();
    }
    else {
      qCritical() << "Could not create default configuration file:" << config.getPath();
    }
  }  
}

AgentConfig::~AgentConfig() {
  if (tree) {
    delete tree;
  }
}

bool AgentConfig::save() {
  if (!tree) return false;
  return config.commit(tree);
}

void AgentConfig::print(QDebug dbg) const {
  if (tree) {
    tree->print(dbg);
  }
}

void AgentConfig::load() {
  tree = config.parse();
  valid = tree;

  if (config.getErrors().testFlag(Config::PathNonExistent)) {
    return;
  }

  if (!valid) {
    qCritical() << "Could not load/parse config file:" << config.getPath();
    return;
  }

  // Set the values for type-safe retrieval.
  valid = false;
  qDebug() << "Checking configuration file.. ";

  ConfigTreeNode *node = tree->searchNode("AgentConfig");
  if (!node) {
    qCritical() << "The root element must be 'AgentConfig'!";
    return;
  }

  // AgentConfig/Host
  node = tree->searchNode("AgentConfig/Host");
  if (!node) {
    qCritical() << "Must have an entry 'AgentConfig/Host'!";
    return;
  }
  QVariant var = node->getValue();
  hostVar = var.toString();
  // TODO: do check of host name!!!
  if (var.isNull()) {
    qCritical() << "AgentConfig/Host needs to be a string!";
    return;
  }    

  // AgentConfig/Port
  node = tree->searchNode("AgentConfig/Port");
  if (!node) {
    qCritical() << "Must have an entry 'AgentConfig/Port'!";
    return;
  }
  var = node->getValue();
  bool ok;
  portVar = var.toString().toUInt(&ok);  
  if (var.isNull() || !ok) {
    qCritical() << "AgentConfig/Port needs to be an unsigned 16-bit integer!";
    return;
  }

  valid = true;
}

void AgentConfig::writeDefault() {
  if (tree) delete tree;
  tree = DefaultConfig::create();
  valid = save();
}
