#include "ZBSender.h"

ZBSender::ZBSender(int fd, std::mutex * zbSenderConditionVariableMutex, std::condition_variable * zbSenderConditionVariable, PacketQueue * zbSendQueue) : fileDescriptor(fd), zbSenderConditionVariableMutex(zbSenderConditionVariableMutex), zbSenderConditionVariable(zbSenderConditionVariable), zbSendQueue(zbSendQueue)
{
	std::cout << "ZBSender constructor" << std::endl;
}

void ZBSender::operator() ()
{
	while(true)
	{
		std::unique_lock<std::mutex> lu(*zbSenderConditionVariableMutex);
		zbSenderConditionVariable->wait(lu, [this]{return !zbSendQueue->empty();});
		ZBPacket * packet;

		while(!zbSendQueue->empty())
		{
			if(typeid(packet) ==  typeid(LibelAddNodePacket *) || typeid(packet) ==  typeid(LibelRequestIOPacket *) || typeid(packet) ==  typeid(LibelChangeFreqPacket *) || typeid(packet) ==  typeid(LibelChangeNodeFreqPacket *) )
			{
				std::cout << "Sendable packet received in ZBSender" << std::endl;
				packet = dynamic_cast<ZBPacket *> (zbSendQueue->getPacket());
				std::cout << "sending : " << *packet << std::endl;
				write(fileDescriptor, (void*) packet->getEncodedPacket().data(),  packet->getEncodedPacket().size());
				fsync(fileDescriptor);		
			}
		}
	}

}
