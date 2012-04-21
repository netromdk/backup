#ifndef PACKET_H
#define PACKET_H

#include <QByteArray>

/**
 * Abstract base class for packets.
 */
class Packet {
public:
  enum Kind {
    State
  };

  virtual ~Packet() { }

  Kind getKind() const { return kind; }

  /**
   * Get next portion of data to be sent. 'max' determines the maximum
   * bytes to retrieve if available.
   */
  virtual QByteArray getData(qint64 max) = 0;

protected:
  Packet(Kind kind) : kind(kind) { }

private:
  Kind kind;
};

#endif // PACKET_H
