#include "Key.h"

namespace crypto {
  RSA *getRsaKey(const QSslKey &key) {
    if (key.algorithm() == QSsl::Rsa) {
      RSA *rsa = (RSA*) key.handle();
      if (RSA_check_key(rsa)) {
        return rsa;
      }
    }
    return NULL;
  }
 
  DSA *getDsaKey(const QSslKey &key) {
    if (key.algorithm() == QSsl::Dsa) {
      return (DSA*) key.handle();
    }
    return NULL;    
  }
}
