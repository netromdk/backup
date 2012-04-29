#ifndef UTILITY_H
#define UTILITY_H

#include <QString>
#include <QStringList>

namespace util {
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

    /**
     * Get the user name of the current user.
     */
    static QString getUserName();

    /**
     * Convert CLI arguments to a string list keeping string literals
     * if present.
     */
    static QStringList argsToList(int argc, char **argv);

    /**
     * Prompt for input. 'requireInput' determines whether it will
     * continue until non-empty input is given.
     */
    static QString prompt(const QString &msg, bool requireInput = true);
  };
}

#endif // UTILITY_H
