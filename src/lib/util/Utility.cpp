#include <QRegExp>
#include <QTextStream>
#include <QHostAddress>

#include "Env.h"
#include "Utility.h"

namespace util {
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

  QStringList Utility::argsToList(int argc, char **argv) {
    QStringList args;
    for (int i = 1; i < argc; i++) {
      QString arg(argv[i]);
      bool strlit = (arg.indexOf(" ") != -1);
      args.append((strlit ? "\"" : "") + arg + (strlit ? "\"" : ""));
    }
    return args;
  }

  QString Utility::prompt(const QString &msg, bool requireInput) {
    QTextStream stdIn(stdin, QIODevice::ReadOnly),
      stdOut(stdout, QIODevice::WriteOnly);
    stdIn.setCodec("UTF-8");
    stdIn.setAutoDetectUnicode(true);

  start:
    stdOut << msg;
    stdOut.flush();
    
    QString line = stdIn.readLine();

    // If EOF was reached then recreate stream.
    if (requireInput && stdIn.atEnd()) {
      stdOut << "\n";
      stdOut.flush();
      return prompt(msg, requireInput);
    }

    line = line.trimmed();
    if (requireInput && line.isEmpty()) {
      goto start;
    }

    return line;
  }
}
