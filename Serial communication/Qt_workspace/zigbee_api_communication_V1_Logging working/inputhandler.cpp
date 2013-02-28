#include "inputhandler.h"

InputHandler::InputHandler(const InputHandler& source)
{
	std::cout << "Copy constructor" << std::endl;
	fileDescriptor = source.fileDescriptor;
	//logFile = source.logFile; //ropen("./log.txt", "a");
}

InputHandler::InputHandler(int fd) : fileDescriptor(fd)
{	
	std::cout << "constructor" << std::endl;
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

void InputHandler::operator() ()
{
	int input = 0x0;
	int count = 0;
	logFile.open("log.txt");
	logFile << "start test" << std::endl;
	
	std::cout << "fileDescriptor in inputhandler: " << fileDescriptor << std::endl;
	while(1)
    	{
		read(fileDescriptor, &input, 1);
		if(input == 0x7E)
		{
			std::cout << std::endl << std::endl << "previous packetsize : " << count << std::endl;
			logFile << std::endl << std::endl << "previouspacketSize : " << count << std::endl;
			count = 0;

			printf("0: %X\n",  input);
			logFile << std::hex <<  input << std::flush;

			read(fileDescriptor, &input, 1);
			printf("1: %X\n",  input);
			logFile << std::hex <<  input << std::flush;
			int packetSize = input * 255;

			read(fileDescriptor, &input, 1);
			packetSize += input;
			printf("2: %X\n",  input);
			logFile << std::hex << input << std::flush;

			unsigned char packet[packetSize];

			for(int position = 0; position < packetSize; ++position)
			{
				read(fileDescriptor, &input, 1);
				packet[position] = input;
				count++;
				printf("   %X\n",  input);
				logFile << std::hex << input << std::flush;
				fflush(stdout);
			}

			for(int position = 0; position < packetSize; ++position)
			{
				printf("          %X\n",  packet[position]);

				fflush(stdout);
			}

			printf("          	%X\n",  packet[21]);
			printf("          	%X\n",  packet[22]);
			float sensorVoltage = ((256 * packet[21] + packet[22]) * 1.2) / 0x3FF ;
			printf("sensor voltage: %f\n",  sensorVoltage);
			logFile << std::endl << "sensor voltage: " << sensorVoltage << std::endl;
			fflush(stdout);

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
