#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QList>
#include <QObject>
#include <QString>
#include <QSqlError>
#include <QSqlRecord>
#include <QStringList>
#include <QSqlDatabase>

/**
 * Provides an interface to a SQLite 3.x database.
 */
class DatabaseManager : public QObject {
public:
  /**
   * Get the manager instance - If calling this the first time during
   * runtime then the path has to be set to the database to load.
   */
  static DatabaseManager *getInstance(const QString &path = QString());

  /**
   * Checks that the SQLite driver is available.
   */
  static bool isSupported();

  virtual ~DatabaseManager();

  /**
   * Determine whether the database connection is open and valid.
   */
  bool isOpen() const { return db.isValid() && db.isOpen(); }

  /**
   * Enable/disable foreign key checks.
   */
  void enableForeignKeys(bool enable);

  /**
   * Retrieve the last database error.
   */
  QSqlError getError() const { return db.lastError(); }

  /**
   * Check if any error has occurred.
   */
  bool hasError() const { return getError().isValid(); }

  /**
   * Execute specified query on the database.
   */
  bool executeQuery(const QString &query);

  /**
   * Drops table.
   */
  bool dropTable(const QString &name);

  /**
   * Get list of tables in the database.
   */
  QStringList getTables() const;

  /**
   * Check if table exists.
   */
  bool tableExists(const QString &name) const;

  /**
   * Get record of specified table. The record will consist of all
   * columns (but not rows!) and their types and settings.
   */
  QSqlRecord getTableRecord(const QString &name);

  /**
   * Add records to the specified table.
   */
  bool addTableRecords(const QString &name, const QList<QSqlRecord> &records);  

  /**
   * Add a record to the specified table.
   */
  bool addTableRecord(const QString &name, const QSqlRecord &record);
    
private:
  DatabaseManager(const QString &path);
  
  static DatabaseManager *instance;
  QSqlDatabase db;
};

#endif // DATABASE_MANAGER_H