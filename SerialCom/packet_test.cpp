#include "packets/outgoingpacket.h"
#include "../testclass.h"

int main(int argc, char ** argv)
{
	std::vector<unsigned char> data;
	data.push_back(0x10);
	data.push_back(0x24);
	data.push_back(0x25);
	data.push_back(0x26);
	OutgoingPacket packet(0xA, data, ZB_TRANSMIT_REQUEST);
	TestClass::assert((packet.getSizeLSB() + packet.getSizeMSB() * 256) == static_cast<int>(data.size() + 1), std::string("ZBPacket::getLSB and getMSB"));
	TestClass::assert(packet.getFrameData() == data, "ZBPacket::getData");
	TestClass::assert(packet.getFrameType() == 0xA, "ZBPacket::getFrameType");
	
	return 0;
}
