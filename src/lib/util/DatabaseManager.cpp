#include <QDebug>
#include <QSqlQuery>
#include <QFileInfo>
#include <QCoreApplication>

#include "DatabaseManager.h"

DatabaseManager *DatabaseManager::instance = NULL;

DatabaseManager *DatabaseManager::getInstance(const QString &path) {
  if (!instance) {
    if (path.isEmpty()) {
      return NULL;
    }
    
    instance = new DatabaseManager(path);
  }
  
  return instance;
}

bool DatabaseManager::isSupported() {
  return QSqlDatabase::isDriverAvailable("QSQLITE");
}

DatabaseManager::DatabaseManager(const QString &path) {
  connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(deleteLater()));

  QFileInfo info(path);
  if (info.exists() && !info.isWritable()) {
    qCritical() << "Database file exists and is not writable!";
    return;
  }

  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(path);
  db.open();

  if (db.isOpen()) {
    // Foreign keys are disabled by default.
    enableForeignKeys(true);
  }
}

DatabaseManager::~DatabaseManager() {
  if (db.isOpen()) {
    db.close();
  }
}

void DatabaseManager::enableForeignKeys(bool enable) {
  db.exec("PRAGMA foreign_keys = " + QString(enable ? "ON" : "OFF"));  
}

bool DatabaseManager::executeQuery(const QString &query) {
  db.exec(query);
  return !hasError();
}

bool DatabaseManager::dropTable(const QString &name) {
  db.exec("DROP TABLE IF EXISTS " + name);
  return !hasError();
}

QStringList DatabaseManager::getTables() const {
  return db.tables();
}

bool DatabaseManager::tableExists(const QString &name) const {
  return getTables().contains(name);
}
