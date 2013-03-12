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
ERROR(InvalidXMLError, "XML passed was invalid")
ERROR(IpsumError, "error occured in connection with ipsum")
ERROR(SerialError, "Couldn't open serial port, check if the device is connected correctly and if the port number is right")


#endif
