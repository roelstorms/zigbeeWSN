#include "libeliumIOpacket.h"

LibeliumIOPacket::LibeliumIOPacket(std::vector<unsigned char> input) : DataPacket(input, ZB_LIBEL_IO)
{
	std::vector<bool> mask;
	unsigned char maskChar = data.at(2);
	nodeIdentifier = data.at(1);
	for(int i = 0; i < 8; ++i)
	{	
		mask.push_back(maskChar & 0x01);
		maskChar = maskChar >> 1;
	}
	int count = 3;
	float value;
	if(mask.at(0) == 1)
	{
		value = getData().at(count++) * 256 + getData().at(count++);
		sensorData.insert(std::pair<SensorType, float>(PLUVIO, value));
		value = 0;
	}

	if(mask.at(1) == 1)
	{
		value = getData().at(count++) * 256 + getData().at(count++);
		sensorData.insert(std::pair<SensorType, float>(VANE, value));
		value = 0;
	}

	if(mask.at(2) == 1)
	{
		value = getData().at(count++) * 256 + getData().at(count++);
		sensorData.insert(std::pair<SensorType, float>(ANEMO, value));
		value = 0;
	}
	if(mask.at(3) == 1)
	{
		value = getData().at(count++) * 256 + getData().at(count++);
		sensorData.insert(std::pair<SensorType, float>(CO2, value));
		value = 0;
	}

	if(mask.at(4) == 1)
	{
		value = getData().at(count++);
		(std::pair<SensorType, float>(BAT, value));
		value = 0;
	}

	if(mask.at(5) == 1)
	{
		value = getData().at(count++) * 256 + getData().at(count++);
		value /= 100;
		value += 500;
		sensorData.insert(std::pair<SensorType, float>(PRES, value));
		value = 0;
	}

	if(mask.at(6) == 1)
	{
		value = getData().at(count++) * 256 + getData().at(count++);
		sensorData.insert(std::pair<SensorType, float>(HUM, value));
		value = 0;
	}

	if(mask.at(7) == 1)
	{
		value = getData().at(count++) * 256 + getData().at(count++);
		value *= 10;
		value -= 40;
		sensorData.insert(std::pair<SensorType, float>(TEMP, value));
		value = 0;
	}

}

unsigned char LibeliumIOPacket::getNodeIdentifier() const
{
	return nodeIdentifier;
}


