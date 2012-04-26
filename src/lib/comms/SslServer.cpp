#include <QSslCipher>
#include <QSslConfiguration>

#include "SslServer.h"
#include "Connection.h"

namespace comms {
  SslServer::SslServer(const QString &cert, const QString &key)
    : cert(cert), key(key)
  {
    setSecurityParameters();
  }

  void SslServer::incomingConnection(int descriptor) {
    emit newConnection(new Connection(descriptor, cert, key));
  }

  void SslServer::setSecurityParameters() {
    // Set default SSL configuration.
    QSslConfiguration sslConf = QSslConfiguration::defaultConfiguration();
    sslConf.setProtocol(QSsl::TlsV1SslV3);

    // Disallow all ciphers using MD5, RC4 and DES including those using
    // less than 128 bits. Only use SSLv3/TLSv1.
    QList<QSslCipher> ciphersAllowed;
    foreach (const QSslCipher &cipher, sslConf.ciphers()) {
      QString name = cipher.name().toLower(),
        crypt = cipher.encryptionMethod().toLower();
      if (name.contains("md5") || name.contains("des") || crypt.contains("rc4")
          || (cipher.protocol() != QSsl::SslV3 && cipher.protocol() != QSsl::TlsV1)) {
        continue;
      }
      ciphersAllowed.append(cipher);
    }

    if (ciphersAllowed.size() == 0) {
      qCritical() << "No ciphers were available and allowed!";
    }

    sslConf.setCiphers(ciphersAllowed);

    // "Disables the insertion of empty fragments into the data when
    // using block ciphers. When enabled, this prevents some attacks
    // (such as the BEAST attack)."
    if (sslConf.testSslOption(QSsl::SslOptionDisableEmptyFragments)) {
      sslConf.setSslOption(QSsl::SslOptionDisableEmptyFragments, true);
    }

    // "Disables the older insecure mechanism for renegotiating the
    // connection parameters."
    if (sslConf.testSslOption(QSsl::SslOptionDisableLegacyRenegotiation)) {
      sslConf.setSslOption(QSsl::SslOptionDisableLegacyRenegotiation, true);
    }  

    QSslConfiguration::setDefaultConfiguration(sslConf);
  }
}
