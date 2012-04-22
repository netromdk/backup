#ifndef SIGN_H
#define SIGN_H

#include <QSslKey>
#include <QByteArray>

namespace crypto {
  bool sign(const QByteArray &data, const QSslKey &key, QByteArray &sig);
}

#endif // SIGN_H
