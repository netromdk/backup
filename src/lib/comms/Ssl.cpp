#include <QFile>
#include <QDebug>
#include <QSslKey>
#include <QDateTime>
#include <QSslCertificate>

#include "Ssl.h"

Ssl::Errors Ssl::checkCert(const QString &cert) {
  QList<QSslCertificate> sslCerts = QSslCertificate::fromPath(cert);
  if (sslCerts.size() == 0) {
    qWarning() << "No certificates found.";
    return NoCerts;
  }

  if (sslCerts.size() > 1) {
    qWarning() << "Multiple certificates found.";
    return MultipleCerts;
  }

  QSslCertificate sslCert = sslCerts[0];
  if (sslCert.isNull() || !sslCert.isValid()) {
    qWarning() << "Certificate not valid.";
    return NotValid;
  }

  QDateTime effective = sslCert.effectiveDate(), expiry = sslCert.expiryDate(),
    now = QDateTime::currentDateTime();

  if (now < effective) {
    qWarning() << "Certificate not effective until" << qPrintable(effective.toString());
    return NotEffective;
  }

  if (now > expiry) {
    qWarning() << "Certificate expired on" << qPrintable(expiry.toString());
    return Expired;
  }

  QSslKey pubKey = sslCert.publicKey();
  if (pubKey.isNull()) {
    qWarning() << "Invalid public key with certificate.";
    return InvalidPubKey;
  }
  
  return NoError;
}

Ssl::Errors Ssl::checkKey(const QString &key) {
  QFile file(key);
  if (!file.open(QIODevice::ReadOnly)) {
    qWarning() << "Could not read key.";
    return NotValid;
  }
  
  QByteArray data = file.readAll();
  QSslKey sslKey(data, QSsl::Rsa);
  if (sslKey.isNull()) {
    sslKey = QSslKey(data, QSsl::Dsa);
    if (sslKey.isNull()) {
      qWarning() << "Key is invalid. Must to use either RSA or DSA.";
      return NotValid;
    }
  }

  int advisedBits = 2048;
  if (sslKey.length() < advisedBits) {
    qWarning().nospace()
      << "Key length is only " << sslKey.length()
      << " bits. It is advised to use at least a "
      << advisedBits << "-bit key.";
  }
  
  return NoError;
}
