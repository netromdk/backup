#ifndef STATE_PACKET_H
#define STATE_PACKET_H

#include <QVariantMap>

#include "Packet.h"

#define STATE_PACKET_SIZE 65536 // bytes

/**
 * Provides a packet for storing key=value pairs using QString for the
 * keys and QVariant for the values.
 */
class StatePacket : public Packet {
public:
  StatePacket();
  
  static StatePacket *fromData(QByteArray &data);

  virtual QByteArray getData(qint64 max = STATE_PACKET_SIZE);
  void setData(QByteArray &data);

  QVariantMap getDataMap() const { return dataMap; }
  
  QVariant &operator[](const QString &key);
  QVariant operator[](const QString &key) const;

private:
  void encode();
  void decode();
  
  QVariantMap dataMap;
  bool encoded;
  QByteArray data;
};

#endif // STATE_PACKET_H
