#ifndef OUTGOINGPACKET_H
#define OUTGOINGPACKET_H

class OutgoingPacket : public ZBPacket
{
	private:

	public:
		OutgoingPacket(std::vector<unsigned char> data, PacketType packetType );

};

#endif
