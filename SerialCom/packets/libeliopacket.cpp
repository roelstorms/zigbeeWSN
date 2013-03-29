
#include "libeliopacket.h"

LibelIOPacket::LibelIOPacket(std::vector<unsigned char> input) : DataPacket(input, ZB_LIBEL_IO)
{
	std::vector<bool> mask;
	std::cout << "LibelIOPacket constructor" << std::endl;
	std::cout << "data length: " << data.size() << std::endl;
	// Bits in the mask have this meaning: 15,14,13,12,11,10,9,8,PLUVIO, ANEMO, CO2, BAT, PRES, HUMID, TEMP

	unsigned int maskChar = data.at(5) * 256 + data.at(6);
	nodeIdentifier = data.at(1);
	for(int i = 0; i < 16; ++i)
	{	
		mask.push_back(maskChar & 0x0001);
		maskChar = maskChar >> 1;
	}
	int count = 3;
	float value;
	if(mask.at(7) == 1)
	{
		value = getData().at(count++) * 256 + getData().at(count++);
		sensorData.insert(std::pair<SensorType, float>(PLUVIO, value));
		value = 0;
	}

	if(mask.at(6) == 1)
	{
		value = data.at(count++) * 256 + getData().at(count++);
		sensorData.insert(std::pair<SensorType, float>(VANE, value));
		value = 0;
	}

	if(mask.at(5) == 1)
	{
		value = data.at(count++) * 256 + getData().at(count++);
		sensorData.insert(std::pair<SensorType, float>(ANEMO, value));
		value = 0;
	}
	if(mask.at(4) == 1)
	{
		value = data.at(count++) * 256 + getData().at(count++);
		sensorData.insert(std::pair<SensorType, float>(CO2, value));
		value = 0;
	}

	if(mask.at(3) == 1)
	{
		value = data.at(count++);
		(std::pair<SensorType, float>(BAT, value));
		value = 0;
	}

	if(mask.at(2) == 1)
	{
		value = getData().at(count++) * 256 + getData().at(count++);
		value /= 100;
		value += 500;
		sensorData.insert(std::pair<SensorType, float>(PRES, value));
		value = 0;
	}

	if(mask.at(1) == 1)
	{
		value = getData().at(count++) * 256 + getData().at(count++);
		sensorData.insert(std::pair<SensorType, float>(HUM, value));
		value = 0;
	}

	if(mask.at(0) == 1)
	{
		value = getData().at(count++) * 256 + getData().at(count++);
		value *= 10;
		value -= 40;
		sensorData.insert(std::pair<SensorType, float>(TEMP, value));
		value = 0;
	}

}

unsigned char LibelIOPacket::getNodeIdentifier() const
{
	return nodeIdentifier;
}


