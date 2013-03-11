#include "connection.h"

Connection::Connection(std::string portNumber)
{

	std::string device("/dev/ttyUSB");
	device.append(portNumber);
	
	std::cout << "device : " << device << std::endl;
	const char * address = device.c_str();
	connectionDescriptor = open(address , O_RDWR | O_NOCTTY | O_NDELAY);
	std::cout << "connectionDescripto: " << connectionDescriptor << std::endl;
 	if (connectionDescriptor == -1)
 	{
		/*
		* Could not open the port.
		*/
		std::cerr << "open_port: Unable to open " << address << std::endl;
		throw SerialError();
	}
   	else
    	{
		std::cout << "set up connection" << std::endl;
		fcntl(connectionDescriptor, F_SETFL, FNDELAY);		// Set the port to unblocking
		//fcntl(connectionDescriptor, F_SETFL, 0);		// Set the port to blocking
    	}
	
	// 9600 baud, NO parity, 1 stop bit
		
    	struct termios options;
    	tcgetattr(connectionDescriptor, &options);

	//options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag = B9600;		//Set baudrate to 9600 baud
	options.c_cflag |= CS8;	
	options.c_cflag |= CLOCAL;
	// no parity 8N1
	options.c_cflag &= ~PARENB;		// Set parity bit
	options.c_cflag &= ~CSTOPB;		// Set Stopbit
	options.c_cflag &= ~CSIZE;		
	options.c_cflag |= CREAD;		
	options.c_cflag |= CS8;		
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_cc[VTIME] = 0;
	options.c_cc[VMIN] = 1;
	tcsetattr(connectionDescriptor , TCSANOW, &options);
	tcflush(connectionDescriptor, TCIFLUSH);
	tcflush(connectionDescriptor, TCOFLUSH);  
}

Connection::~Connection()
{
	closeConnection();
}

bool Connection::sendPacket(std::vector<unsigned char> packet)
{
	char data[] = "Test";
	//write(connectionDescriptor, data, 4); 	
	write(connectionDescriptor, (void*) packet.data(), packet.size());
	fsync(connectionDescriptor);
	std::cout << "Packet sent: ";
	for(int i = 0; i < packet.size(); ++i)
	{
		std::cout << std::uppercase << std::setw(2) << std::setfill('0') << std::hex << (int) *(packet.data() + i);
		//std::cout << std::hex << (int)packet.at(i);
	}
	std::cout << std::endl;
	return true;
}

void Connection::startInputHandler()
{
}

void Connection::closeConnection()
{	
	std::cout << "Closing connection file descriptor" << std::endl;
	close(connectionDescriptor);
}

int Connection::getConnectionDescriptor()
{
	return connectionDescriptor;
}
