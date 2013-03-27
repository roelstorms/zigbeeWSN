#ifndef WSPACKET_H
#define WSPACKET_H
#include <string>
#include "../errors.h"
#include "../packet.h"

enum RequestType
{
	CHANGE_FREQUENCY
};

class WSPacket : public Packet
{
	private:
		RequestType requestType;
		std::string data;
	public:
		WSPacket(std::string aURI, std::string aData) throw (WebserviceInvalidCommand);
		~WSPacket();
		const RequestType& getRequestType() const;
		const std::string& getRequestData() const;
};

#endif

