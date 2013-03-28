#include "ZBReceiver.h"


ZBReceiver::ZBReceiver(int fd, std::mutex * aConditionVariableMutex, std::condition_variable * aMainConditionVariable, PacketQueue * aZBReceiveQueue) : fileDescriptor(fd), conditionVariableMutex(aConditionVariableMutex), mainConditionVariable(aMainConditionVariable), zbReceiveQueue(aZBReceiveQueue)
{	
	std::cout << "ZBReceiver constructor" << std::endl;
}

ZBReceiver::~ZBReceiver()
{
	std::cout << "ZBReceiver destructor" << std::endl;
}

unsigned char ZBReceiver::readByte(int fd)
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


void ZBReceiver::operator() ()
{
	unsigned char input = 0x0;
	int count = 0;
	std::vector<unsigned char> packetVector;	
	while(true)
    	{
		input = readByte(fileDescriptor);
		if(input == 0x7E)
		{
			packetVector.push_back(input);
			
			input = readByte(fileDescriptor);
			int packetSize = input * 255;
			packetVector.push_back(input);

			input = readByte(fileDescriptor);
			packetSize += input;
			packetVector.push_back(input);
	
			printf("pSize: %d\n", packetSize);
			for(int position = 0; position <= packetSize; ++position)
			{
				input = readByte(fileDescriptor);
				packetVector.push_back(input);
				fflush(stdout);
			}
			unsigned char packetType = packetVector.at(3);	
			std::cout << "packet type: " << std::uppercase << std::setw(2) << std::setfill('0') << std::hex  << (int) packetType << std::endl;
			
			Packet * packet;
			switch(packetType)
			{
				case 0x90:
					switch(packetVector.at(15))	//It is a ZB data packet, all our libelium packets are of this type, so now to figure out what libelium packet we'e got
					{
						case 0x02:
							packet = dynamic_cast<Packet*> (new LibelIOPacket(packetVector));
							zbReceiveQueue->addPacket(packet);
							{
							std::lock_guard<std::mutex> lg(*conditionVariableMutex);
							mainConditionVariable->notify_all();
							}
						break;

						default:
						throw UnknownPacketType();
							
					}

					break;

				case 0x92:
					//packet = dynamic_cast<Packet*> (new DataIOPacket(packetVector));
					break;

				case 0x88:
					std::cout << "ATCommandResponsePacket received, and thrown away" << std::endl;
						//Processing needed here
				break;
				default :
				throw UnknownPacketType();

			}

			packetVector.clear();
		//	std::cout << "analog data on pin 1: " << std::to_string(APIPacket.readAnalog(0)) << std::endl;
		}
    	}
	logFile.close();
	std::cout << "End of inputhandler" << std::endl;	
}
