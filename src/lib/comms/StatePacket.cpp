#include <QDataStream>

#include "StatePacket.h"

namespace comms {
  StatePacket::StatePacket() : Packet(State), encoded(false), first(true) { }

  StatePacket *StatePacket::fromData(const QByteArray &data) {
    StatePacket *packet = new StatePacket;
    packet->setData(data);
    return packet;
  }

  QByteArray StatePacket::getData(qint64 max) {
    if (!encoded) encode();
  
    QByteArray res;

    // Prepend the size of the data to the data so the other side knows
    // how much to read.
    if (first) {
      first = false;
      QDataStream stream(&res, QIODevice::WriteOnly);
      stream << (qint32) data.size();
    }

    // Take chunk of data.
    int size = res.size();
    res.append(data.left(max - size));
    data = data.mid(res.size() - size);
    return res;
  }

  void StatePacket::setData(const QByteArray &data) {
    this->data = data;
    decode();
  }

  QVariant &StatePacket::operator[](const QString &key) {
    return dataMap[key];
  }

  QVariant StatePacket::operator[](const QString &key) const {
    return dataMap[key];
  }

  void StatePacket::encode() {
    data.clear();
    QDataStream stream(&data, QIODevice::WriteOnly);
    stream << dataMap;
    data = qCompress(data);
    encoded = true;
  }

  void StatePacket::decode() {
    dataMap.clear();
    QDataStream stream(qUncompress(data));
    stream >> dataMap;
  }
}
