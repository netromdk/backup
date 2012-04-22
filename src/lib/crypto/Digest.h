#ifndef DIGEST_H
#define DIGEST_H

#include <QByteArray>

#include <openssl/obj_mac.h>

namespace crypto {
  enum DigestAlgorithm {
    SHA_224 = NID_sha224,
    SHA_256 = NID_sha256,
    SHA_384 = NID_sha384,
    SHA_512 = NID_sha512
  };

  /**
   * Compute the message digest of data using the specified algorithm.
   */
  QByteArray digest(const QByteArray &data, DigestAlgorithm alg);
}

#endif // DIGEST_H
