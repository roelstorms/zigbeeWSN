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
		const PacketType& getType() const;

		// Purpose of this function is to make packets bind virtually as needed by the dynamic cast to put packets in a queueu.
		virtual void bindVirtually();
};

#endif
