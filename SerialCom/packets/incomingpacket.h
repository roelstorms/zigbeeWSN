#ifndef INCOMINGPACKET_H
#define INCOMINGPACKET_H

class IncomingPacket : public ZBPacket
{
	private:

	public:
		IncompingPacket(std::vector<unsigned char> input, PacketType packetType);

};

#endif
