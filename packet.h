#ifndef PACKET_H
#define PACKET_H
#include "errors.h"

enum PacketType		
{
	ZB_IO, ZB_TRANSMIT_REQUEST, ZB_LIBEL_IO, ZB_LIBEL_CHANGEFREQ, ZB_LIBEL_CHANGEFREQ_REPLY, ZB_LIBEL_ADDNODE, ZB_LIBEL_ADDNODE_REPLY,  WS_COMMAND, IPSUM_UPLOAD,
	first = ZB_LIBEL_IO, last = WS_COMMAND
};


class Packet
{
	private:
		PacketType type;
		Packet(Packet&);
		Packet(const Packet&);
		Packet& operator=(const Packet&);

	public:
		Packet(PacketType aType) throw (InvalidPacketType);
		virtual const PacketType& getType() const;

};

#endif
