#ifndef TRANSMITREQUESTPACKET_H
#define TRANSMITREQUESTPACKET_H
#include "ZBPacket.h"
#include "../../enums.h"
#include "../../errors.h"
#include <sstream>

class TransmitRequestPacket : ZBPacket
{

	private:

	public:
		TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64Bit, PacketType ZB_LIBEL_ADDNODE);
};

#endif

