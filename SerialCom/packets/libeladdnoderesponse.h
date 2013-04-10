#ifndef LIBELADDNODERESPONSE_H 
#define LIBELADDNODERESPONSE_H


#include <string>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include "receivepacket.h"
#include <iomanip>
#include <map>
#include "../../errors.h"
#include "../../enums.h"
#include "libeladdnodepacket.h"

class LibelAddNodeResponse : public ReceivePacket 
{
	private:
	public:
		LibelAddNodeResponse(std::vector<unsigned char> input);
		PacketType getPacketType(){ return ZB_LIBEL_ADD_NODE_RESPONSE; };
		bool correspondsTo(LibelAddNodePacket * packet);
};

#endif


