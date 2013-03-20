#ifndef ERRORS_H
#define ERRORS_H

#define ERROR(name, message) \
class name : public std::exception \
{ \
public: \
	const char* what() const noexcept \
	{ \
		return message; \
	} \
};

#include <exception>

ERROR(HttpError, "HTTP error using libcurl")
ERROR(InvalidLogin, "Login to ipsum database failed, check password and username")
ERROR(InvalidXMLError, "XML passed was invalid")
ERROR(IpsumError, "error occured in connection with ipsum")
ERROR(SerialError, "Couldn't open serial port, check if the device is connected correctly and if the port number is right")
ERROR(unknownPacketType, "this type of packet can not be decoded or does not exist, check the datasheet for more information. If the packet type doesn't exist there must have been an undetected transmission error")
ERROR(UnknownDataType, "The datatype you chose for one of the fields is not recognized.")
ERROR(WebserviceInvalidCommand, "Command specified by the URL has not been recognized")
#endif
