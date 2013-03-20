#ifndef WEBSERVICEREQUEST_H
#define WEBSERVICEREQUEST_H
#include <string>
#include "../errors.h"


enum RequestType
{
	CHANGE_FREQUENCY
};

class WebserviceRequest
{
	private:
		RequestType requestType;
		std::string data;
	public:
		WebserviceRequest(std::string aURI, std::string aData) throw (WebserviceInvalidCommand);
		~WebserviceRequest();
		const RequestType& getRequestType() const;
		const std::string& getRequestData() const;
};

#endif

