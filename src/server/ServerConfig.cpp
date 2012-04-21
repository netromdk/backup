#include <QDir>

#include "util/Paths.h"
#include "ServerConfig.h"
#include "DefaultConfig.h"

ServerConfig::ServerConfig() : tree(NULL), valid(false) {
  QDir().mkpath(Paths::getConfigDir());
  config.setPath(Paths::getConfigDir() + "/server.conf");
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

ServerConfig::~ServerConfig() {
  if (tree) {
    delete tree;
  }
}

bool ServerConfig::save() {
  if (!tree) return false;
  return config.commit(tree);
}

void ServerConfig::print(QDebug dbg) const {
  if (tree) {
    tree->print(dbg);
  }
}

void ServerConfig::load() {
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

  ConfigTreeNode *node = tree->searchNode("ServerConfig");
  if (!node) {
    qCritical() << "The root element must be 'ServerConfig'!";
    return;
  }

  // ServerConfig/Port
  node = tree->searchNode("ServerConfig/Port");
  if (!node) {
    qCritical() << "Must have an entry 'ServerConfig/Port'!";
    return;
  }
  QVariant var = node->getValue();
  bool ok;
  portVar = var.toString().toUInt(&ok);  
  if (var.isNull() || !ok) {
    qCritical() << "ServerConfig/Port needs to be an unsigned 16-bit integer!";
    return;
  }

  // ServerConfig/SslCert
  node = tree->searchNode("ServerConfig/SslCert");
  if (!node) {
    qCritical() << "Must have an entry 'ServerConfig/SslCert'!";
    return;
  }
  var = node->getValue();
  sslCertVar = var.toString();
  // TODO: check file exists and that it is a proper SSL certificate!
  if (var.isNull()) {
    qCritical() << "ServerConfig/SslCert needs to point to a X.509 certificate in PEM format!";
    return;
  }

  // ServerConfig/SslKey
  node = tree->searchNode("ServerConfig/SslKey");
  if (!node) {
    qCritical() << "Must have an entry 'ServerConfig/SslKey'!";
    return;
  }
  var = node->getValue();
  sslKeyVar = var.toString();
  // TODO: check file exists and that it is a proper SSL private key!
  if (var.isNull()) {
    qCritical() << "ServerConfig/SslKey needs to point to a X.509 private key in PEM format!";
    return;
  }    

  valid = true;
}

void ServerConfig::writeDefault() {
  if (tree) delete tree;
  tree = DefaultConfig::create();
  valid = save();
}
