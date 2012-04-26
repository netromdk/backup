#ifndef SSL_H
#define SSL_H

#include <QFlags>
#include <QString>

namespace comms {
  /**
   * Auxiliary functions regarding SSL.
   */ 
  class Ssl {
  public:
    enum Error {
      NoError = 0x0,
      NotValid,

      // Certificate errors.
      NoCerts,
      MultipleCerts,
      NotEffective,
      Expired,
      InvalidPubKey
    };
    Q_DECLARE_FLAGS(Errors, Error);
  
    static Errors checkCert(const QString &cert);
    static Errors checkKey(const QString &key);  
  };

  Q_DECLARE_OPERATORS_FOR_FLAGS(Ssl::Errors);
}

#endif // SSL_H
