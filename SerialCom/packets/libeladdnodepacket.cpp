#include "libeladdnodepacket.h"

LibelAddNodePacket::LibelAddNodePacket(std::vector<unsigned char> zigbeeAddress64bit, std::vector<SensorType> sensors) : TransmitRequestPacket(zigbeeAddress64bit)
{
	std::vector<unsigned char> rfData;
	int mask;
	for( auto it = sensors.begin(); it < sensors.end(); ++it)
	{
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
	
	addRFData(rfData);
}

