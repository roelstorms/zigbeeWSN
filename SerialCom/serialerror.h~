#ifndef HTTPERROR_H
#define HTTPERROR_H
#include <exception>

class HttpError : public std::exception
{

	public :
	
		const char* what() const noexcept
		{
			return "HTTP error using libcurl"; 
		}


};

#endif
