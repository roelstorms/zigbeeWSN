#include "packets/outgoingpacket.h"
#include "../testclass.h"
#include <typeinfo>
#include "../enums.h"
#include "packets/libelchangefreqpacket.h"
#include "packets/libeliopacket.h"
#include "packets/libeladdnodepacket.h"
#include <cmath>
int main(int argc, char ** argv)
{
	//Testing OutgoingPacket
	std::vector<unsigned char> data;
	data.push_back(0xA);
	data.push_back(0x24);
	data.push_back(0x25);
	data.push_back(0x26);
	OutgoingPacket packet(data);
	TestClass::assert((packet.getSizeLSB() + packet.getSizeMSB() * 256) == static_cast<int>(data.size() ), std::string("ZBPacket::getLSB and getMSB"));
	TestClass::assert(packet.getFrameData() == data, "ZBPacket::getData");
	TestClass::assert(packet.getFrameType() == 0xA, "ZBPacket::getFrameType");
	std::cout << "typeid: " << typeid(packet).name() << std::endl;


	//Testing LibelChangeFrequencyPacket
	std::cout << "Starting ChangeFreqPacket test" << std::endl;
	std::vector<unsigned char> destinationZB64BitAddress{0XAD, 0XAD, 0XAD, 0XAD, 0XAD, 0XAD, 0XAD, 0XAD};
	

	std::vector<std::pair <SensorType, int>> newFrequencies;
	newFrequencies.push_back(std::pair<SensorType, int>(TEMP, 10));
	newFrequencies.push_back(std::pair<SensorType, int>(PRES, 30));
	newFrequencies.push_back(std::pair<SensorType, int>(BAT, 5));
	newFrequencies.push_back(std::pair<SensorType, int>(CO2, 2));
	LibelChangeFreqPacket libelChangeFreqPacket( destinationZB64BitAddress, newFrequencies);
	std::cout << "The created packet looks like this : " << libelChangeFreqPacket << std::endl;
		
	std::vector<unsigned char> expectedFrameData{0x10, 0x00, 0xAD, 0xAD, 0xAD, 0xAD,0xAD, 0xAD, 0xAD, 0xAD, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x1D, 0x00, 0x0A, 0x00, 0x1E, 0x00, 0x05, 0x00, 0x02};
	
	TestClass::assert(libelChangeFreqPacket.getFrameType() == 0x10, "libelChangeFreqPacket::getFrameType");
	TestClass::assert(libelChangeFreqPacket.getFrameData() == expectedFrameData, "libelChangeFreqPacket::getFrameData");


	//Testing LibelIOPacket
	std::vector<unsigned char> input{0X7E, 0X00/*size*/, 0X15/*size*/, 0X90, 0XAD, 0XAD, 0XAD, 0XAD, 0XAD, 0XAD, 0XAD, 0XAD, 0XFF, 0XFE, 0X00, 0X00, 0X1D, 0X18 /*temp1*/, 0XC4 /*temp2*/, 0XBB /*Pres1*/, 0XB2 /*Pres2*/, 0X58 /*Bat*/, 0X01 /*CO2*/, 0X90 /*CO2*/, 0XBB /*checksum*/ };
	LibelIOPacket libelIOPacket(input);
	TestClass::assert(floor(libelIOPacket.getTemperature()*10)/10 == 23.4, "libelIOPacket::getTemperature");
	TestClass::assert(floor(libelIOPacket.getPressure()*10)/10 == 980.5, "libelIOPacket::getPressure");
	TestClass::assert(floor(libelIOPacket.getBattery()) == 88, "libelIOPacket::getBattery");
	TestClass::assert(floor(libelIOPacket.getCO2()*10)/10 == 400, "libelIOPacket::getCO2");
	
	bool testErrorHandling = false;
	try
	{
		libelIOPacket.getHumidity();
	}
	catch(DataNotAvailable)
	{
		testErrorHandling = true;
	}
	TestClass::assert(testErrorHandling, "libelIOPacket::getHumidity | errorhandling check");



	//Testing libelAddNodePacket

	std::vector<unsigned char> zigbeeAddress64bit{0XAB, 0XAB, 0XAB, 0XAB, 0XAB, 0XAB, 0XAB, 0XAB};
	std::vector<SensorType> sensors{TEMP, HUM, CO2};
	LibelAddNodePacket libelAddNodePacket (zigbeeAddress64bit, sensors);	 	
	std::cout << "Libeladdnodepacket: " << libelAddNodePacket << std::endl;
	std::cout << "RFData: " << std::endl;
#ifdef DEBUG
	std::vector<unsigned char> rfData = libelAddNodePacket.getRFData();
	for(auto it = rfData.begin(); it < rfData.end(); ++it)
	{
		std::cout << std::setfill('o') << std::hex << std::setw(2) <<  (int)(*it) << std::endl;
	}
#endif	
      	TestClass::assert(libelAddNodePacket.getRFData() == std::vector<unsigned char>{0x00, 0X13}, "libelAddNodePacket checking if mask is set correctly");	
	return 0;
}
