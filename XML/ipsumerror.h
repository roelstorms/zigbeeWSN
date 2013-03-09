#ifndef IPSUMERROR_H 
#define v_H
#include <exception>

class IpsumError : public std::exception
{

	public :
	
		const char* what() const noexcept
		{
			return "error occured in connection with ipsum"; 
		}


};

#endif
