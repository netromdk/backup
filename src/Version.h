#ifndef VERSION_H
#define VERSION_H

#include <QString>

#define MAJOR_VERSION 0
#define MINOR_VERSION 1
#define BUILD_VERSION 0

#define BUILD_DATE "April 15th, 2012"

#define MAJOR_FACTOR 1000000
#define MINOR_FACTOR 1000

static inline QString versionString(int major, int minor, int build, bool showDate = true) {
  return QString::number(major) + "." + QString::number(minor) + "." +
    QString::number(build) + (showDate ? " [" + QString(BUILD_DATE) + "]" : "");
}

static inline QString versionString(bool showDate = true) {
  return versionString(MAJOR_VERSION, MINOR_VERSION, BUILD_VERSION, showDate);
}

static inline QString versionString(int version, bool showDate = true) {
  int major = version / MAJOR_FACTOR,
    minor = (version / MINOR_FACTOR) - (major * (MAJOR_FACTOR / MINOR_FACTOR)),
    build = version - (major * MAJOR_FACTOR + minor * MINOR_FACTOR);
  return versionString(major, minor, build, showDate);
}

static inline int versionNumber(int major = MAJOR_VERSION,
                                int minor = MINOR_VERSION,
                                int build = BUILD_VERSION) {
  return major * MAJOR_FACTOR + minor * MINOR_FACTOR + build;
}

#endif // VERSION_H
