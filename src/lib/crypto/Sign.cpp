#include <openssl/objects.h>

#include "Key.h"
#include "Sign.h"

namespace crypto {
  bool sign(const QByteArray &data, const QSslKey &key, DigestAlgorithm alg,
            QByteArray &sig) {
    const unsigned char *cdata = (const unsigned char*) data.constData();
    
    switch (key.algorithm()) {
    case QSsl::Rsa: {
      RSA *rsa = getRsaKey(key);
      if (!rsa) return false;
      unsigned char *sigret = new unsigned char[RSA_size(rsa)];
      unsigned int siglen;
      if (RSA_sign(alg, cdata, data.size(), sigret, &siglen, rsa)) {
        sig = QByteArray((char*) sigret, siglen);        
        return true;
      }
      break;
    }

    case QSsl::Dsa: {
      DSA *dsa = getDsaKey(key);
      if (!dsa) return false;
      unsigned char *sigret = new unsigned char[DSA_size(dsa)];
      unsigned int siglen;      
      if (DSA_sign(alg, cdata, data.size(), sigret, &siglen, dsa)) {
        sig = QByteArray((char*) sigret, siglen);        
        return true;
      }
      break;
    }
    }

    return false;
  }

  bool verify(const QByteArray &sig, const QByteArray &data, const QSslKey &key,
              DigestAlgorithm alg) {
    unsigned char *cdata = (unsigned char*) data.constData(),
      *csig = (unsigned char*) sig.constData();
    
    switch (key.algorithm()) {
    case QSsl::Rsa: {
      RSA *rsa = getRsaKey(key);
      if (!rsa) return false;
      if (RSA_verify(alg, cdata, data.size(), csig, sig.size(), rsa)) {
        return true;
      }
      break;
    }

    case QSsl::Dsa: {
      DSA *dsa = getDsaKey(key);
      if (!dsa) return false;
      if (DSA_verify(alg, cdata, data.size(), csig, sig.size(), dsa)) {
        return true;
      }      
      break;
    }
    }

    return false;      
  }
}
