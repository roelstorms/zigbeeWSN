#include "inputhandler.h"

InputHandler::InputHandler(const InputHandler& source)
{
	stop = source.stop;
	fileDescriptor = source.fileDescriptor;
	std::cout << "Copy constructor" << std::endl;
	std::cout << "adress of stop in Inputhandler::Inputhandler: " << stop << std::endl;
	//logFile = source.logFile; //ropen("./log.txt", "a");
}

InputHandler::InputHandler(int fd, bool * a_stop) : fileDescriptor(fd), stop(a_stop)
{	
	std::cout << "constructor" << std::endl;
	std::cout << "adress of stop in Inputhandler::Inputhandler: " << stop << std::endl;
	//logFile.open("./log.txt");
	//logFile << "test" << std::endl;
	//logFile.close();
}

InputHandler::~InputHandler()
{
	//if(logFile.is_open())
	{
	//	logFile.close();	
	}
	//fwrite("Stop test\n\n", 1, 13, logFile);
	std::cout << "destructor" << std::endl;
}

unsigned char InputHandler::readByte(int fd)
{

	int input = 0x0;
	while(read(fd, &input, 1) <= 0)
	{

	}
	printf("%X\n", input);
	if(input == 0x7D)
	{
		while(read(fd, &input, 1) <= 0)
		{

		}
		std::cout << "input: " << std::hex << input << std::endl;	
		input = input ^ 0x20;
		std::cout << "XOR'ed input: " << std::hex << input << std::endl;	
	}
	return input;
	
	//return 0x0;	// Not correct since input could be 0X0 as well. A bool should be returned to let the caller know if a byte was read or not. 
			// A pointer to a buffer could be passed as argument to store the unsigned char read from fd. 
			// Need to figure out where I want to put the blocking while loop that waits for input. In this function or somewhere when this function is called.
}


void InputHandler::operator() ()
{
	unsigned char input = 0x0;
	int count = 0;
	logFile.open("log.txt");
	logFile << "start test" << std::endl;
	std::cout << "bool stop in inputhandler: " << *stop << std::endl;	
	std::cout << "fileDescriptor in inputhandler: " << fileDescriptor << std::endl;
	while(*stop != true)
    	{
		//std::cout << "stop inside inputhandler while loop: " << *stop << std::endl;
		input = readByte(fileDescriptor);
		//std::cout << "input in while loop: " << std::hex << input << std::endl;
		if(input == 0x7E)
		{
			
			std::cout << std::endl << std::endl << "previous packetsize : " << count << std::endl;
			logFile << std::endl << std::endl << "previous packetSize : " << count << std::endl;
			count = 0;

			input = readByte(fileDescriptor);
			//packet[1] = input;
			printf("1: %X\n",  input);
			logFile << std::hex <<  input << std::flush;
			int packetSize = input * 255;

			input = readByte(fileDescriptor);
			//packet[2] = input;
			packetSize += input;	
			//packetSize--; 		// Will contain the size of the data contained in the packets, this excludes the checksum
			printf("2: %X\n",  input);
			logFile << std::hex << input << std::flush;
			

			//read(fileDescriptor, &input, 1);	// will contain type identifier
			
			unsigned char packet[packetSize+ 1 ];
			std::cout << "packetsize derived from packet info: " << packetSize << std::endl;
			printf("pSize: %d\n", packetSize);
			for(int position = 0; position <= packetSize; ++position)
			{
				input = readByte(fileDescriptor);
				packet[position] = input;
				count++;
				printf("   %d: %X\n",  position, input);
				logFile << std::hex << input << std::flush;
				fflush(stdout);
			}
			int sum = 0;
			for(int position = 0; position <= packetSize; ++position)
			{
				printf("          %d: %X\n",  position, packet[position]);
				fflush(stdout);
				sum += packet[position];
			        std::cout << "		sum : " << std::hex << sum << std::endl;	
			}
			printf("sum: %X\n", sum);
			//sum = sum + packet[packetSize];	
			printf("sum: %X\n", sum);
			//std::cout << "sum: " << std::hex << sum << std::endl;
			//check packet integrity
			
			

			printf("          	%X\n",  packet[18]);
			printf("          	%X\n",  packet[19]);
			float sensorVoltage = ((256 * packet[18] + packet[19]) * 1.2) / 0x3FF ;
			printf("sensor voltage: %f\n",  sensorVoltage);
			logFile << std::endl << "sensor voltage: " << sensorVoltage << std::endl;
			


			Http socket(std::string("http://ipsum.groept.be"));
			socket.login();
			socket.uploadData(sensorVoltage);//data);

			//dh(sensorVoltage);	
			
			
			fflush(stdout);

		}
		/*else
		{
			count++;
			printf("%X\n",  input);
			fprintf(logFile, "%X\n",  input);
			fflush(stdout);
		}*/
    	}
	logFile.close();
	std::cout << "End of inputhandler" << std::endl;	
}
