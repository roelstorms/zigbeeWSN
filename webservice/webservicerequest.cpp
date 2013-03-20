#include "webservicerequest.h"

WebserviceRequest::WebserviceRequest(std::string aURI, std::string aData) throw(WebserviceInvalidCommand) : data(aData)
{
	if(aURI.find("changeFrequency") != std::string::npos)
	{
		requestType = CHANGE_FREQUENCY;
	}
	else
	{
		throw WebserviceInvalidCommand();
	}

}

WebserviceRequest::~WebserviceRequest()
{

}

const RequestType&  WebserviceRequest::getRequestType() const
{
	return requestType;
}

const std::string& WebserviceRequest::getRequestData() const
{
	return data;
}
