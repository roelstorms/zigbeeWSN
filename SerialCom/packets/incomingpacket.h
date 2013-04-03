#ifndef INCOMINGPACKET_H
#define INCOMINGPACKET_H
#include "ZBPacket.h"
#include "../../errors.h"

class IncomingPacket : public ZBPacket
{
	private:

	public:
	void bindVirtually(){};

	IncomingPacket(std::vector<unsigned char> input) throw (CorruptedPacket);

};

#endif
