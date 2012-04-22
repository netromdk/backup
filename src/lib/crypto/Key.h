#ifndef KEY_H
#define KEY_H

#include <QSslKey>

#include <openssl/rsa.h>
#include <openssl/dsa.h>

namespace crypto {
  /**
   * Retrieve raw RSA key from QSslKey. Also checks validity.
   */
  RSA *getRsaKey(const QSslKey &key);

  /**
   * Retrieve raw DSA key from QSslKey. Also checks validity.
   */  
  DSA *getDsaKey(const QSslKey &key);  
}

#endif // KEY_H
