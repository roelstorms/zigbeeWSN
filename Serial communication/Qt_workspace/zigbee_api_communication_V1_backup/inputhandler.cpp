#include "inputhandler.h"

InputHandler::InputHandler(int fd) : fileDescriptor(fd)
{
	//std::cout << "constructor" << std::endl;
}

InputHandler::~InputHandler()
{
	//fwrite("Stop test\n\n", 1, 13, logFile);
	//std::cout << "destructor" << std::endl;
}

void InputHandler::operator() ()
{
	unsigned char input;
	int count = 0;
	logFile = fopen("./log.txt", "a");
	fwrite("Start test", 1, 10, logFile);
	
	std::cout << "fileDescriptor in inputhandler: " << fileDescriptor << std::endl;
	while(1)
    {
		//std::cout << "bytes read: " << read(fileDescriptor, input, 1) << std::endl;
		read(fileDescriptor, &input, 1);
		fwrite(&input, 1, 4, logFile);
		if(input == 0x7E)
		{
			std::cout << std::endl << std::endl << "previous packetsize : " << count << std::endl;
			//std::cout << "packet received, size : " << packetSize << std::endl;
			count = 0;

			printf("0: %X\n",  input);
			fprintf(logFile, " %X\n",  input);

			read(fileDescriptor, &input, 1);
			printf("1: %X\n",  input);
			fprintf(logFile, " %X\n",  input);
			int packetSize = input * 255;

			read(fileDescriptor, &input, 1);
			packetSize += input;
			printf("2: %X\n",  input);
			fprintf(logFile, " %X\n",  input);

			unsigned char packet[packetSize];

			for(int position = 0; position < packetSize; ++position)
			{
				read(fileDescriptor, &input, 1);
				packet[position] = input;
				count++;
				printf("   %X\n",  input);
				fprintf(logFile, "%X\n",  input);
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
	fclose(logFile);
}
