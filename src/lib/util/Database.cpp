#include <QDebug>
#include <QSqlQuery>
#include <QFileInfo>
#include <QSqlTableModel>
#include <QCoreApplication>

#include "Database.h"

namespace util {
  Database *Database::instance = NULL;

  Database *Database::getInstance(const QString &path) {
    if (!instance) {
      if (path.isEmpty()) {
        return NULL;
      }
    
      instance = new Database(path);
    }
  
    return instance;
  }

  bool Database::isSupported() {
    return QSqlDatabase::isDriverAvailable("QSQLITE");
  }

  Database::Database(const QString &path) {
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

  Database::~Database() {
    if (db.isOpen()) {
      db.close();
    }
  }

  void Database::enableForeignKeys(bool enable) {
    db.exec("PRAGMA foreign_keys = " + QString(enable ? "ON" : "OFF"));  
  }

  bool Database::executeQuery(const QString &query) {
    db.exec(query);
    return !hasError();
  }

  bool Database::dropTable(const QString &name) {
    db.exec("DROP TABLE IF EXISTS " + name);
    return !hasError();
  }

  QStringList Database::getTables() const {
    return db.tables();
  }

  bool Database::tableExists(const QString &name) const {
    return getTables().contains(name);
  }

  QSqlRecord Database::getTableRecord(const QString &name) {
    return db.record(name);
  }

  bool Database::addTableRecords(const QString &name, const QList<QSqlRecord> &records) {
    if (records.size() == 0) {
      return false;
    }

    QSqlTableModel model;
    model.setTable(name);

    foreach (const QSqlRecord &record, records) {
      // Append record to the end of the table.
      model.insertRecord(-1, record);
    }

    model.submitAll();
    return !hasError();
  }

  bool Database::addTableRecord(const QString &name, const QSqlRecord &record) {
    return addTableRecords(name, QList<QSqlRecord>() << record);
  }
}
