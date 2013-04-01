






#ifndef LIBELADDNODEPACKET_H
#define LIBELADDNODEPACKET_H

#include <string>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include "transmitrequestpacket.h"
#include <iomanip>
#include <map>
#include "../../errors.h"
#include "../../packet.h"
#include "../../enums.h"


class LibelAddNodePacket : public TransmitRequestPacket 
{
	private:
		unsigned char nodeIdentifier;
	public:
		//LibelAddNodePacket(std::vector<unsigned char> input);
		LibelAddNodePacket(std::vector<unsigned char> zigbeeAddress64bit);
		unsigned char getNodeIdentifier() const;
	 	

};

#endif
