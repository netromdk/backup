#ifndef STATE_PACKET_H
#define STATE_PACKET_H

#include <QVariantMap>

#include "Packet.h"

namespace comms {
  /**
   * Provides a packet for storing key=value pairs using QString for the
   * keys and QVariant for the values.
   */
  class StatePacket : public Packet {
  public:
    StatePacket();
  
    static StatePacket *fromData(const QByteArray &data);

    virtual QByteArray getData(qint64 max);
    void setData(const QByteArray &data);

    QVariantMap getDataMap() const { return dataMap; }
  
    QVariant &operator[](const QString &key);
    QVariant operator[](const QString &key) const;

  private:
    void encode();
    void decode();
  
    QVariantMap dataMap;
    bool encoded, first;
    QByteArray data;
  };
}

#endif // STATE_PACKET_H
