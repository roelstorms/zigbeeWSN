
#include "libeladdnoderesponse.h"

LibelAddNodeResponse::LibelAddNodeResponse(std::vector<unsigned char> input) : ReceivePacket(input)
{
	if(getRFData().at(0) != 0X02)
	{
		std::cerr << "Tried to put a packed into a LibelAddNodeResponse that was of the wrong type (see application ID != 0X02)" << std::endl;	
	}
}



bool LibelAddNodeResponse::correlatesWih(LibelAddNodePacket * packet)
{
	if((getZigbee64BitAddress() == packet->getZigbee64BitAddress()))
	{
		
	}

	return false;
}
 
