#include "inputhandler.h"


InputHandler::InputHandler(int fd, std::mutex * aConditionVariableMutex, std::condition_variable * aMainConditionVariable, std::queue<DataIOPacket> * aDataIOPacketQueue,  std::mutex * aDataIOPacketMutex, std::queue<DataPacket> * aDataPacketQueue, std::mutex * aDataPacketMutex ) : fileDescriptor(fd), conditionVariableMutex(aConditionVariableMutex), mainConditionVariable(aMainConditionVariable), dataIOPacketQueue(aDataIOPacketQueue), dataIOPacketMutex(aDataIOPacketMutex), dataPacketQueue(aDataPacketQueue), dataPacketMutex(aDataPacketMutex)
{	
	std::cout << "Inputhandler constructor" << std::endl;
}

InputHandler::~InputHandler()
{
	std::cout << "Inputhandler destructor" << std::endl;
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

/*
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
		else
		{
			count++;
			printf("%X\n",  input);
			fprintf(logFile, "%X\n",  input);
			fflush(stdout);
		}
    	}
	logFile.close();
	std::cout << "End of inputhandler" << std::endl;	
}
*/

void InputHandler::operator() ()
{
	unsigned char input = 0x0;
	int count = 0;
	std::vector<unsigned char> packet;	
	while(true)
    	{
		input = readByte(fileDescriptor);
		if(input == 0x7E)
		{
			packet.push_back(input);
			
			input = readByte(fileDescriptor);
			int packetSize = input * 255;
			packet.push_back(input);

			input = readByte(fileDescriptor);
			packetSize += input;
			packet.push_back(input);
	
			printf("pSize: %d\n", packetSize);
			for(int position = 0; position <= packetSize; ++position)
			{
				input = readByte(fileDescriptor);
				packet.push_back(input);
				fflush(stdout);
			}
			unsigned char packetType = packet.at(3);	
			std::cout << "packet type: " << std::uppercase << std::setw(2) << std::setfill('0') << std::hex  << (int) packetType << std::endl;
			
			DataIOPacket dataIOPacket;
			DataPacket * dataPacket;
			switch(packetType)
			{
				case 0x90:
					dataPacket = new DataPacket(packet);
					std::cout << "packet of type 90 received" << std::endl;
					{
						std::lock_guard<std::mutex> lg(*dataPacketMutex);
						
						dataPacketQueue->push(std::move(*dataPacket));
						std::cout << "packet received in inputhandler: " << dataPacketQueue->front() << std::endl;
						mainConditionVariable->notify_all();
					}
					break;

				case 0x92:
					dataIOPacket = DataIOPacket(packet);
					std::cout << "packet of type 92 received" << std::endl;
					{
						std::lock_guard<std::mutex> lg(*dataIOPacketMutex);
						dataIOPacketQueue->push(std::move(dataIOPacket));
						std::cout << "packet received in inputhandler: " << dataIOPacketQueue->front() << std::endl;
						mainConditionVariable->notify_all();

					}
					break;

				case 0x88:
					std::cout << "ATCommandResponsePacket received, and thrown away" << std::endl;
						//Processing needed here
				break;
				default :
				throw unknownPacketType();

			}
			packet.clear();
		//	std::cout << "analog data on pin 1: " << std::to_string(APIPacket.readAnalog(0)) << std::endl;
		}
    	}
	logFile.close();
	std::cout << "End of inputhandler" << std::endl;	
}
