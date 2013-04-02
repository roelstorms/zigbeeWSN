#include "packets/outgoingpacket.h"
#include "../testclass.h"
#include <typeinfo>

int main(int argc, char ** argv)
{
	std::vector<unsigned char> data;
	data.push_back(0xA);
	data.push_back(0x24);
	data.push_back(0x25);
	data.push_back(0x26);
	OutgoingPacket packet(data);
	TestClass::assert((packet.getSizeLSB() + packet.getSizeMSB() * 256) == static_cast<int>(data.size() ), std::string("ZBPacket::getLSB and getMSB"));
	TestClass::assert(packet.getFrameData() == data, "ZBPacket::getData");
	TestClass::assert(packet.getFrameType() == 0xA, "ZBPacket::getFrameType");
	std::cout << "typeid: " << typeid(packet).name() << std::endl;	
	return 0;
}
