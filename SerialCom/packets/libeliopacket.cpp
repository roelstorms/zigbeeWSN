
#include "libeliopacket.h"

LibelIOPacket::LibelIOPacket(std::vector<unsigned char> input) : ReceivePacket(input)
{
	std::vector<bool> mask;
	std::cout << "LibelIOPacket constructor" << std::endl;
	std::cout << "data length: " << receivedData.size() << std::endl;
	if(receivedData.at(0) != 0X0A)
	{
		std::cerr << "Tried to put a packed into a LibelIOPacket that was of the wrong type (see application ID != 0X0A)" << std::endl;	
	}

	// Bits in the mask have this meaning: 15,14,13,12,11,10,9,8,PLUVIO, ANEMO, CO2, BAT, PRES, HUMID, TEMP
	unsigned int maskChar = receivedData.at(1) * 256 + receivedData.at(2);
	std::cout << "maskchar: " << maskChar << std::endl;
	for(int i = 0; i < 16; ++i)
	{	
		mask.push_back(maskChar & 0x0001);
		maskChar = maskChar >> 1;
	}
	std::cout << "mask: " << std::endl;
#ifdef DEBUG
	for(auto it = mask.begin(); it < mask.end(); ++it)
	{
		std::cout << (*it) << std::endl;
	}
#endif
	std::cout << std::endl << std::endl; 
	int count = 3;
	float value;
	if(mask.at(0) == 1)
	{
		value = receivedData.at(count++) * 256 ;
		value += receivedData.at(count++);
		value /= 100;
		value -= 40;
		sensorData.insert(std::pair<SensorType, float>(TEMP, value));
		std::cout << "Temp data found in packet: " << value << std::endl;
		value = 0;
	}

	if(mask.at(1) == 1)
	{
		value = receivedData.at(count++);
		sensorData.insert(std::pair<SensorType, float>(HUM, value));
		std::cout << "Humidity data found in packet: " << value << std::endl;
		value = 0;
	}

	if(mask.at(2) == 1)
	{
		value = receivedData.at(count++) * 256 ;
		value += receivedData.at(count++);
		value /= 100;
		value += 500;
		sensorData.insert(std::pair<SensorType, float>(PRES, value));
		std::cout << "Pressure data found in packet: " << value << std::endl;
		value = 0;
	}
	
	if(mask.at(3) == 1)
	{
		value = receivedData.at(count++);
		sensorData.insert(std::pair<SensorType, float>(BAT, value));
		std::cout << "Battery data found in packet: " << value << std::endl;
		value = 0;
	
	}
	if(mask.at(4) == 1)
	{
		value = receivedData.at(count++) * 256 ;
		value += receivedData.at(count++);
		sensorData.insert(std::pair<SensorType, float>(CO2, value));
		std::cout << "CO2 data found in packet: " << value << std::endl;
		value = 0;
	}

	if(mask.at(5) == 1)
	{
		value = receivedData.at(count++) * 256 ;
		value += receivedData.at(count++);
		sensorData.insert(std::pair<SensorType, float>(ANEMO, value));
		std::cout << "Anemo data found in packet: " << value << std::endl;
		value = 0;
	}

	if(mask.at(6) == 1)
	{
		value = receivedData.at(count++) * 256 ;
		value += receivedData.at(count++);
		sensorData.insert(std::pair<SensorType, float>(VANE, value));
		std::cout << "Vane data found in packet: " << value << std::endl;
		value = 0;
	}

	if(mask.at(7) == 1)
	{
		value = receivedData.at(count++) * 256 ;
		value += receivedData.at(count++);
		sensorData.insert(std::pair<SensorType, float>(PLUVIO, value));
		std::cout << "Pluvio data found in packet: " << value << std::endl;
		value = 0;
	}
}




