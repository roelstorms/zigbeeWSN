#ifndef CONNECTION_H
#define CONNECTION_H

#include "connection.cpp"


class Connection
{
	private:
	int fileDescriptor;	

	public:
	Connection();
	~Connection();
};

#endif
