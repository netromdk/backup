#include "Digest.h"

#include <openssl/sha.h>

namespace crypto {
  QByteArray digest(const QByteArray &data, DigestAlgorithm alg) {
    const unsigned char *cdata = (const unsigned char*) data.constData();
    
    switch (alg) {
    case SHA_224:
      return QByteArray((char*) SHA224(cdata, data.size(), NULL),
                        SHA224_DIGEST_LENGTH);

    case SHA_256:
      return QByteArray((char*) SHA256(cdata, data.size(), NULL),
                        SHA256_DIGEST_LENGTH);
      
    case SHA_384:
      return QByteArray((char*) SHA384(cdata, data.size(), NULL),
                        SHA384_DIGEST_LENGTH);

    default:
    case SHA_512:
      return QByteArray((char*) SHA512(cdata, data.size(), NULL),
                        SHA512_DIGEST_LENGTH);
    }
  }
}
