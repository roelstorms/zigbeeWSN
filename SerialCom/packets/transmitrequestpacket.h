#ifndef TRANSMITREQUESTPACKET_H
#define TRANSMITREQUESTPACKET_H
#include "outgoingpacket.h"
#include "libelpacket.h"
#include "../../enums.h"
#include "../../errors.h"
#include <sstream>

class TransmitRequestPacket : public  OutgoingPacket, public LibelPacket 
{

	private:

	public:
		TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64bit);
		TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64bit, std::vector<unsigned char> zigbeeAddress16bit, unsigned char receiveOptions );
		
		void addFrameData(std::vector<unsigned char> zigbeeAddress64bit, std::vector<unsigned char> zigbeeAddress16bit, unsigned char receiveOptions );
		void addRFData(std::vector<unsigned char> rfData);
        void addData(std::vector<unsigned char> data);

		virtual std::vector<unsigned char> getMask() const;
		virtual std::vector<unsigned char> getZigbee16BitAddress() const;
		virtual std::vector<unsigned char> getZigbee64BitAddress() const ;
		virtual std::vector<unsigned char> getRFData() const throw (ZbCorruptedFrameData);
        virtual std::vector<unsigned char> getData() const throw(ZbCorruptedFrameData);

};

#endif

