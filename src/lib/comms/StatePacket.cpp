#include <QDataStream>

#include "StatePacket.h"

StatePacket::StatePacket() : Packet(State), encoded(false) { }

StatePacket *StatePacket::fromData(QByteArray &data) {
  StatePacket *packet = new StatePacket;
  packet->setData(data);
  return packet;
}

QByteArray StatePacket::getData(qint64 max) {
  if (!encoded) encode();
  
  QByteArray res;
  if (max > data.size()) {
    res = data;
    data.clear();
    return res;
  }

  res = data.mid(0, max);
  data = data.mid(max);
  return res;
}

void StatePacket::setData(QByteArray &data) {
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
  encoded = true;
}

void StatePacket::decode() {
  dataMap.clear();
  QDataStream stream(data);
  stream >> dataMap;
}

