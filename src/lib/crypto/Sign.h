#ifndef SIGN_H
#define SIGN_H

#include <QSslKey>
#include <QByteArray>

namespace crypto {
  /**
   * Sign data using a key to produce a SHA-512 message digest.
   */
  bool sign(const QByteArray &data, const QSslKey &key, QByteArray &sig);

  /**
   * Verify signature of data using key.
   */
  bool verify(const QByteArray &sig, const QByteArray &data, const QSslKey &key);  
}

#endif // SIGN_H
