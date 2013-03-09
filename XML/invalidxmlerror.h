#ifndef INVALIDXML_H 
#define INXALIDXML_H
#include <exception>

class InvalidXMLError : public std::exception
{

	public :
	
		const char* what() const noexcept
		{
			return "XML passed was invalid"; 
		}


};

#endif
