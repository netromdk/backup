#ifndef AGENT_H
#define AGENT_H

class Connection;
class AgentConfig;

class Agent {
public:
  Agent();
  virtual ~Agent();
  
private:
  AgentConfig *config;
  Connection *conn;
};

#endif // AGENT_H
