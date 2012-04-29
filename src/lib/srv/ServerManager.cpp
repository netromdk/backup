#include <QDir>
#include <QDebug>
#include <QSqlQuery>

#include "util/Paths.h"
using namespace util;

#include "ServerManager.h"

namespace srv {
  ServerManager::ServerManager() : db(NULL), valid(false) {
    initDB();
  }

  void ServerManager::initDB() {
    valid = false;
    
    QDir().mkpath(Paths::getConfigDir());
    db = Database::getInstance(Paths::getConfigDir() + "/server.db");

    if (!db->isOpen()) return;
    
    // Create tables.
    QString query =
      "CREATE TABLE IF NOT EXISTS Agents ("
      "AID INTEGER PRIMARY KEY AUTOINCREMENT, "
      "Created VARCHAR(23) NOT NULL, " // "YYYY-MM-DD HH:MM:SS.SSS"
      "ID TEXT NOT NULL, "
      "PSW BLOB NOT NULL" // SHA-512 digest of password.
      ")";
    if (!db->executeQuery(query)) {
      qWarning() << "Could not create Agents table" << db->getError();
      return;
    }

    // TODO: maybe create a table for attempted/successful logins.. Or
    // just put it in the log.

    valid = true;    
  }

  bool ServerManager::agentIdExists(const QString &id) {
    QSqlQuery query;
    query.prepare("SELECT ID FROM Agents WHERE ID = ?");
    query.addBindValue(id);
    query.exec();

    if (query.first()) {
      return true;
    }
    
    return false;
  }
  
  void ServerManager::addAgent(const QString &id, const QByteArray &pswDig) {
    QSqlQuery query;
    query.prepare("INSERT INTO Agents (Created, ID, PSW) VALUES (?, ?, ?)");
    query.addBindValue(Database::dateToString(QDateTime::currentDateTime()));
    query.addBindValue(id);
    query.addBindValue(pswDig);
    query.exec();
  }

  void ServerManager::removeAgent(const QString &id) {
    QSqlQuery query;
    query.prepare("DELETE FROM Agents WHERE ID = ?");
    query.addBindValue(id);
    query.exec();
  }
  
  void ServerManager::removeAllAgents() {
    QSqlQuery query;
    query.prepare("DELETE FROM Agents");
    query.exec();    
  }

  AgentInfo ServerManager::getAgent(const QString &id) {
    AgentInfo info;

    QSqlQuery query;
    query.prepare("SELECT Created, PSW FROM Agents WHERE ID = ?");
    query.addBindValue(id);
    query.exec();

    if (query.first()) {
      info.created = Database::stringToDate(query.value(0).toString());
      info.id = id;
      info.pswDigest = query.value(1).toByteArray();      
    }
    
    return info;
  }
  
  QList<AgentInfo> ServerManager::getAgents() {
    QList<AgentInfo> agents;

    QSqlQuery query("SELECT ID FROM Agents");
    query.exec();

    while (query.next()) {
      agents.append(getAgent(query.value(0).toString()));
    }
    
    return agents;
  }
}
