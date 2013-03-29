#include "wspacket.h"

WSPacket::WSPacket(std::string aURI, std::string aData) throw(WebserviceInvalidCommand) : Packet(WS_COMMAND), data(aData)
{
	
	if(aURI.find("changeFrequency") != std::string::npos)
	{
		requestType = CHANGE_FREQUENCY;
	}
	else if(aURI.find("addNode"))
	{
		requestType = ADD_NODE;
	}
	else if(aURI.find("addSensor"))
	{
		requestType = ADD_SENSOR;
	}
	else if(aURI.find("requestData"))
	{
		requestType = ADD_SENSOR;
	}
	else
	{
		throw WebserviceInvalidCommand();
	}
	
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
