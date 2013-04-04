#include "libelchangenodefreqpacket.h"

LibelChangeNodeFreqPacket::LibelChangeNodeFreqPacket(std::vector<unsigned char> destinationZB64bitAddress, int newFrequency) : TransmitRequestPacket(destinationZB64bitAddress)
{
	std::vector<unsigned char> rfData;

	rfData.push_back(0x05);		// Libelium application ID, 05 means CH_NODE_FREQ_REQ	
	
	rfData.push_back(newFrequency / 256);	
	rfData.push_back(newFrequency % 256);	

	addRFData(rfData);
}
