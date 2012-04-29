#include <QDebug>

#include "util/Utility.h"
using namespace util;

#include "crypto/Digest.h"

#include "srv/ServerManager.h"
using namespace srv;

#include "AgentContext.h"

void AgentContext::execute(const CommandTreeNode *node, QVariantMap &options,
                          QVariantList &posCmds, QStringList &extData) {
  ServerManager mgr;
  
  if (node->getName() == "add") {
    QString id;
    if (posCmds.size() == 1) {
      id = posCmds[0].toString();
    }
    
    forever {
      if (id.isEmpty()) {
        id = Utility::prompt("Enter ID: ");
      }
        
      if (mgr.agentIdExists(id)) {
        qWarning() << "Agent ID already exists. Try another.";
        id.clear();
        continue;
      }

      break;
    }

    QString psw, psw2;
    forever {
      // TODO: make non-echo prompt.
      psw = Utility::prompt("Enter password: ");
      psw2 = Utility::prompt("Confirm password: ");

      if (psw != psw2) {
        qWarning() << "Passwords did not match. Try again.";
        continue;
      }

      break;
    }

    QByteArray pswDig = crypto::digest(psw.toUtf8(), crypto::SHA_512);
    mgr.addAgent(id, pswDig);

    qDebug() << "Added new agent" << id;
  }

  else if (node->getName() == "remove") {
    bool all = options.contains("all"),
      force = options.contains("force");

    if (all) {
      if (!force && Utility::prompt("Are you sure you want to proceed? [Y/N] ").toLower() != "y") {
        qDebug() << "Aborting";
        return;
      }
      
      mgr.removeAllAgents();
      qDebug() << "Removed all agents";
    }
    else {
      if (posCmds.size() == 0) {
        qWarning() << "Specify the agent ID";
        return;
      }
      
      QString id = posCmds[0].toString();
      if (!mgr.agentIdExists(id)) {
        qWarning() << "Agent id" << id << "does not exist";
        return;
      }

      if (!force && Utility::prompt("Are you sure you want to proceed? [Y/N] ").toLower() != "y") {
        qDebug() << "Aborting";
        return;
      }      
      
      mgr.removeAgent(id);
      qDebug() << "Removed agent" << id;
    }
  }

  else if (node->getName() == "list") {
    QList<AgentInfo> agents;
    if (posCmds.size() == 1) {
      QString id = posCmds[0].toString();

      if (!mgr.agentIdExists(id)) {
        qWarning() << "Agent id" << id << "does not exist";
        return;
      }
      
      agents.append(mgr.getAgent(id));
    }
    else {
      agents = mgr.getAgents();
    }
    
    foreach (const AgentInfo &agent, agents) {
      qDebug() << "Agent" << agent.id;
      qDebug() << "Created" << qPrintable(agent.created.toString());
      qDebug();
    }
  }    
}
