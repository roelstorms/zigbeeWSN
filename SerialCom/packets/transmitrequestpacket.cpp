#include "transmitrequestpacket.h"

TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64Bit, PacketType type) : ZBPacket(ZB_TRANSMIT_REQUEST)
{

}
