#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSslSocket>

class Connection : public QSslSocket {
  Q_OBJECT
  
public:
  Connection();
  Connection(int socketDescriptor, const QString &cert, const QString &key);

public slots:
  void handshake();

private slots:
  void onDataReady();
  void onEncrypted();
  void onSslErrors(const QList<QSslError>&);
  void onPeerVerifyError(const QSslError&);

private:
  void init();

  bool serverMode;
};

#endif // CONNECTION_H
