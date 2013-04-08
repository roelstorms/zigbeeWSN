#ifndef LIBELCHANGENODEFREQ_H
#define LIBELCHANGENODEFREQ_H

#include <string>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>

#include "../../errors.h"
#include "transmitrequestpacket.h"
#include "../../enums.h"



class LibelChangeNodeFreqPacket : public TransmitRequestPacket 
{
	private:
	public:
		
		LibelChangeNodeFreqPacket(std::vector<unsigned char> destinationZB64bitAddress, int newFrequency);
	
		PacketType getPacketType(){ return ZB_LIBEL_CHANGENODEFREQ; };

		
};

#endif


