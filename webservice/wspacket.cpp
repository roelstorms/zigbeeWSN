#include "wspacket.h"

WSPacket::WSPacket(std::string aURI, std::string aData) throw(WebserviceInvalidCommand) : Packet(WS_COMMAND), data(aData)
{
	/*
	   if(aURI.find("changeFrequency") != std::string::npos)
	{
		requestType = CHANGE_FREQUENCY;
	}
	else
	{
		throw WebserviceInvalidCommand();
	}
	*/
}

WSPacket::~WSPacket()
{

}

const RequestType&  WSPacket::getRequestType() const
{
	return requestType;
}

const std::string& WSPacket::getRequestData() const
{
	return data;
}
