#include "libelchangefreqpacket.h"

LibelChangeFreqPacket::LibelChangeFreqPacket(std::vector<unsigned char> destinationZB64bitAddress, std::vector<std::pair<SensorType, int>> newFrequencies) : TransmitRequestPacket(destinationZB64bitAddress)
{
	std::vector<unsigned char> rfData;
	int mask;	
	for(auto it = newFrequencies.begin(); it < newFrequencies.end(); ++it)
	{
		switch((*it).first)
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
	std::cout << "calculated mask in libelchangefreqpacket constructor: " << mask << std::endl;	
	rfData.push_back(mask / 256);
	rfData.push_back(mask % 256);

	for(auto it = newFrequencies.begin(); it < newFrequencies.end(); ++it)
	{
		rfData.push_back((*it).second / 256);	
		rfData.push_back((*it).second % 256);	
	}
	addRFData(rfData);
}
