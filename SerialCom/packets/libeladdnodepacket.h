






#ifndef LIBELADDNODEPACKET_H
#define LIBELADDNODEPACKET_H

#include <string>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include "datapacket.h"
#include <iomanip>
#include <map>
#include "../../errors.h"
#include "../../packet.h"
#include "../../enums.h"


class LibelAddNodePacket : public DataPacket
{
	private:
		unsigned char nodeIdentifier;
	public:
		LibelAddNodePacket(std::vector<unsigned char> input);
		unsigned char getNodeIdentifier() const;
	 	

};

#endif
