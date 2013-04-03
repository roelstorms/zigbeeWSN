#ifndef TRANSMITREQUESTPACKET_H
#define TRANSMITREQUESTPACKET_H
#include "outgoingpacket.h"
#include "../../enums.h"
#include "../../errors.h"
#include <sstream>

class TransmitRequestPacket : public  OutgoingPacket 
{

	private:
		std::vector<unsigned char> frameData;
	public:
		TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64bit);
		TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64bit, std::vector<unsigned char> zigbeeAddress16bit, unsigned char receiveOptions );
		
		void addFrameData(std::vector<unsigned char> zigbeeAddress64bit, std::vector<unsigned char> zigbeeAddress16bit, unsigned char receiveOptions );
		void addRFData(std::vector<unsigned char> rfData);
		std::vector<unsigned char> getRFData();
};

#endif

