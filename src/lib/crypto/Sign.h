#ifndef SIGN_H
#define SIGN_H

#include <QSslKey>
#include <QByteArray>

#include "Digest.h"

namespace crypto {
  /**
   * Sign data using a key to produce a message digest using the
   * specified algorithm.
   */
  bool sign(const QByteArray &data, const QSslKey &key, DigestAlgorithm alg,
            QByteArray &sig);

  /**
   * Verify signature of data using key and specified digest algorithm
   * used at the time of signing.
   */
  bool verify(const QByteArray &sig, const QByteArray &data, const QSslKey &key,
              DigestAlgorithm alg);  
}

#endif // SIGN_H
