#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include <QList>
#include <QString>
#include <QByteArray>

#include "util/Database.h"

namespace srv {
  struct AgentInfo {
    QDateTime created;
    QString id;
    QByteArray pswDigest;
  };
  
  class ServerManager {
  public:
    ServerManager();
    virtual ~ServerManager() { }

    bool isValid() const { return valid; }

    bool agentIdExists(const QString &id);
    void addAgent(const QString &id, const QByteArray &pswDig);
    void removeAgent(const QString &id);
    void removeAllAgents();
    AgentInfo getAgent(const QString &id);    
    QList<AgentInfo> getAgents();

  private:
    void initDB();

    util::Database *db;
    bool valid;
  };
}

#endif // SERVER_MANAGER_H
