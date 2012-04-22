#include <openssl/objects.h>

#include "Key.h"
#include "Sign.h"

namespace crypto {
  bool sign(const QByteArray &data, const QSslKey &key, QByteArray &sig) {
    const unsigned char *cdata = (const unsigned char*) data.constData();
    
    switch (key.algorithm()) {
    case QSsl::Rsa: {
      RSA *rsa = getRsaKey(key);
      if (!rsa) return false;
      unsigned char *sigret = new unsigned char[RSA_size(rsa)];
      unsigned int siglen;
      if (RSA_sign(NID_sha512, cdata, data.size(), sigret, &siglen, rsa)) {
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
      if (DSA_sign(NID_sha512, cdata, data.size(), sigret, &siglen, dsa)) {
        sig = QByteArray((char*) sigret, siglen);        
        return true;
      }
      break;
    }
    }

    return false;
  }
}
