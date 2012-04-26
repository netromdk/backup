#include <QRegExp>
#include <QHostAddress>

#include "Env.h"
#include "Utility.h"

bool Utility::checkHostName(const QString &host) {
  static QRegExp exp("(([a-zA-Z]|[a-zA-Z][a-zA-Z0-9\\-]*[a-zA-Z0-9])\\.)*([A-Za-z]|[A-Za-z][A-Za-z0-9\\-]*[A-Za-z0-9])",
                     Qt::CaseInsensitive);
  return exp.exactMatch(host);
}

bool Utility::checkIP(const QString &ip) {
  QHostAddress adr;
  return adr.setAddress(ip);
}

bool Utility::checkHostOrIP(const QString &str) {
  return checkHostName(str) || checkIP(str);
}

QString Utility::getUserName() {
  QString user;
  
#ifdef WIN
  user = Env::get("%USERNAME%");
#elif UNIX
  user = Env::get("USER");
#endif
  
  return user;
}
