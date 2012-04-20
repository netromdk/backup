#ifndef SERVER_H
#define SERVER_H

class SslServer;
class ServerConfig;

class Server {
public:
  Server();
  virtual ~Server();
  
private:
  ServerConfig *config;
  SslServer *server;
};

#endif // SERVER_H
