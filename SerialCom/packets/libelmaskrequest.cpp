#include "libelmaskrequest.h"

LibelMaskRequest::LibelMaskRequest(std::vector<unsigned char> zigbeeAddress64bit) : TransmitRequestPacket(zigbeeAddress64bit)
{
	std::vector<unsigned char> rfData;
	rfData.push_back(0x03);		// Libelium application ID's, O3 is for MASK_REQUEST
		
	addRFData(rfData);
}

