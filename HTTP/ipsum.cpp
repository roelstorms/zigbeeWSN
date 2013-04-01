#include "ipsum.h"

Ipsum::Ipsum(PacketQueue * ipsumSendQueue, PacketQueue * ipsumReceiveQueue, std::mutex * mainConditionVariableMutex, std::condition_variable * mainConditionVariable, std::mutex * ipsumConditionVariableMutex, std::condition_variable * ipsumConditionVariable) : ipsumSendQueue(ipsumSendQueue), ipsumReceiveQueue(ipsumReceiveQueue), mainConditionVariableMutex(mainConditionVariableMutex), mainConditionVariable(mainConditionVariable), ipsumConditionVariableMutex(ipsumConditionVariableMutex), ipsumConditionVariable(ipsumConditionVariable)
{
	std::cout << "ipsum constructor" << std::endl;
	localIpsumSendQueue = new std::queue<Packet*>;
}

Ipsum::~Ipsum()
{
	delete localIpsumSendQueue;
}

void Ipsum::operator()()
{
	std::cout << "Ipsum::operator()()" << std::endl;

	std::unique_lock<std::mutex> uniqueLock(*ipsumConditionVariableMutex);
	ipsumConditionVariable->wait(uniqueLock, [this] {return (!ipsumSendQueue->empty());});

	std::cout << "ipsum condition variable notified" << std::endl;

	while(!ipsumSendQueue->empty())
	{
		localIpsumSendQueue->push(ipsumSendQueue->getPacket());
	}

	Packet * ipsumPacket;
	while(!localIpsumSendQueue->empty())
	{
		ipsumPacket = localIpsumSendQueue->front();
		localIpsumSendQueue->pop();
		
		switch(ipsumPacket->getType())
		{
			case IPSUM_UPLOAD:
				uploadDataHandler(dynamic_cast<IpsumUploadPacket *> (ipsumPacket));
			break;

			default:
			std::cout << "packet not found" << std::endl;
			// Packet not recognized
		
		}	
	}
}


void Ipsum::uploadDataHandler(IpsumUploadPacket * packet)
{

}
