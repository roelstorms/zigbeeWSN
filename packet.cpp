#include "packet.h"

Packet::Packet(PacketType aType) throw (InvalidPacketType): type(aType)
{
}

const PacketType& Packet::getType() const
{
	return type;
}
