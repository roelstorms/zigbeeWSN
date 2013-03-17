#include "ATCommandPacket.h"


ATCommandPacket::ATCommandPacket(std::vector<unsigned char> aATCommand, std::vector<unsigned char> aParameter, int aFrameID, bool aApplyChangesEnabled) : Packet()
{
	if(aATCommand.size() == 2)
	{
		if(aApplyChangesEnabled)
		{
			encodedPacket.push_back(0x08);
		}
		else
		{
			encodedPacket.push_back(0x09);
		}

		encodedPacket.push_back(aFrameID);
		if(aATCommand.size() != 2)
		{
			std::cout << "ATCommand length is invalid" << std::endl;
			return;
		}
		encodedPacket.push_back(aATCommand.at(0));
		encodedPacket.push_back(aATCommand.at(1));
		for(int i = 0; i < aParameter.size(); ++i)
		{
			encodedPacket.push_back(aParameter.at(i));
		}
		wrap(encodedPacket);
	}
	else
	{
		std::cout << "Length of AT command was incorrect" << std::endl;	// Length of AT command is not correct
	}

}
