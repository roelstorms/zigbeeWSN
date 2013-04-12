#include "libeladdnodepacket.h"

LibelAddNodePacket::LibelAddNodePacket(std::vector<unsigned char> zigbeeAddress64bit, std::vector<SensorType> sensors) : TransmitRequestPacket(zigbeeAddress64bit)
{
	std::vector<unsigned char> rfData;
	int mask;
	rfData.push_back(0x01);		// Libelium application ID's, O1 is for ADD_NODE_REQ
    rfData.push_back(0x01);     // Fragment number = 1 (means number of fragments = 1)
    rfData.push_back('#');      // Indicates first fragment

	for( auto it = sensors.begin(); it < sensors.end(); ++it)
	{
		std::cout << "iterating over all sensors" << std::endl;
		switch(*it)
		{
			case TEMP:
				mask += 0X01;
			break;	
			case HUM:
				mask += 0X02;
			break;	
			case PRES:
				mask += 0X04;
			break;	
			case BAT:
				mask += 0X08;
			break;	
			case CO2:
				mask += 0X10;
			break;	
			case ANEMO:
				mask += 0X20;
			break;	
			case VANE:
				mask += 0X40;
			break;	
			case PLUVIO:
				mask += 0X80;
			break;	
		}
	}
	rfData.push_back(mask / 256);
	rfData.push_back(mask % 256);
	
	std::cout << "rfData calculated in LibelAddNodePacket(), this represents the mask of the noded to be added" << std::endl;
	for(auto it = rfData.begin(); it < rfData.end(); ++it)
	{
		std::cout << std::setfill('0') << std::hex << std::setw(2) <<  (int)(*it) << " ";
	}
	std::cout << std::endl;
	
	addRFData(rfData);
}

