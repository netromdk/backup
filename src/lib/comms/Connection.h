#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSslSocket>

class Connection : public QSslSocket {
  Q_OBJECT
  
public:
  Connection(int socketDescriptor, bool serverMode = false);

private slots:
  void onDataReady();
  void onEncrypted();
  void onSslErrors(const QList<QSslError>&);
  void onPeerVerifyError(const QSslError&);
};

#endif // CONNECTION_H
