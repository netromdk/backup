#ifndef AGENT_H
#define AGENT_H

class AgentConfig;

class Agent {
public:
  Agent();
  virtual ~Agent();
  
private:
  AgentConfig *config;
};

#endif // AGENT_H
