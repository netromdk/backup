#ifndef UTILITY_H
#define UTILITY_H

#include <QString>

class Utility {
public:
  static bool checkHostName(const QString &host);
  static bool checkIP(const QString &ip);  
};

#endif // UTILITY_H
