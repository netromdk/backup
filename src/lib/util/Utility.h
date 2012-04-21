#ifndef UTILITY_H
#define UTILITY_H

#include <QString>

/**
 * Utility functions.
 */
class Utility {
public:
  /**
   * Check if host name is valid.
   */
  static bool checkHostName(const QString &host);

  /**
   * Check if IP address is a valid IPv4 or IPv6 address.
   */
  static bool checkIP(const QString &ip);

  /**
   * Check if input is a valid host name or an IPv4 or IPv6 address.
   */  
  static bool checkHostOrIP(const QString &str);
};

#endif // UTILITY_H
