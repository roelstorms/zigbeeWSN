#ifndef PACKET_H
#define PACKET_H
#include "errors.h"
#include <cstddef>

enum PacketType		
{
	ZB_IO, ZB_TRANSMIT_REQUEST, ZB_LIBEL_MASK_REQUEST, ZB_LIBEL_MASK_RESPONSE, ZB_LIBEL_IO, ZB_LIBEL_REQUEST_IO, ZB_LIBEL_CHANGEFREQ,
       	ZB_LIBEL_CHANGE_FREQ_RESPONSE,ZB_LIBEL_CHANGENODEFREQ, ZB_LIBEL_CHANGE_NODE_FREQ_RESPONSE, ZB_LIBEL_CHANGEFREQ_REPLY, ZB_LIBEL_ADDNODE, 
	ZB_LIBEL_ADD_NODE_RESPONSE, ZB_LIBEL_ADDNODE_REPLY,  WS_COMMAND, IPSUM_UPLOAD,
	first = ZB_LIBEL_IO, last = WS_COMMAND
};


class Packet
{
	private:
		Packet(Packet&);
		Packet(const Packet&);
		Packet& operator=(const Packet&);
	public:
		Packet() throw (InvalidPacketType);

		// Purpose of this function is to make packets bind virtually as needed by the dynamic cast to put packets in a queueu.
		virtual PacketType getPacketType() = 0;
};

#endif
