#include "connection.h"

Connection::Connection(std::string portNumber)
{

	char port[255];
	std::string device("/dev/ttyUSB");


	device.append(portNumber);
	std::cout << "device : " << device << std::endl;
	const char * adres = device.c_str();
	//sprintf(port, adres);
	connectionDescriptor = open(adres , O_RDWR | O_NOCTTY | O_NDELAY);


 	if (connectionDescriptor == -1)
 	{
		/*
		* Could not open the port.
		*/
	
		sprintf(port, "open_port: Unable to open %s", port); // puts string into buffer
		perror(port);
	}
   	else
    	{
		fcntl(connectionDescriptor, F_SETFL, 0);
    	}
	
	// 9600 baud, NO parity, 1 stop bit
		
    	struct termios options;
    	tcgetattr(connectionDescriptor, &options);

	//options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag = B9600;
	options.c_cflag |= CS8;
	options.c_cflag |= CLOCAL;
	// no parity 8N1
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
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

}

bool Connection::sendPacket(std::vector<unsigned char> packet)
{
	char data[] = "Test";
	//write(connectionDescriptor, data, 4); 	
	write(connectionDescriptor, (void*) packet.data(), packet.size());
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
	bool stop = false;
	InputHandler inputHandler(connectionDescriptor, &stop);
	std::cout << "adress of stop in Connection: " << &stop << std::endl;
	boost::thread inputThread(boost::ref(inputHandler));
	
	//std::vector<unsigned char> input(5, 0xBC);
	//inputHandler.API_wrap(input);	
	
	//UserInput ui(&stop);
	//ui();

	//inputThread.join();
}

int Connection::getConnectionDescriptor()
{
	return connectionDescriptor;
}
