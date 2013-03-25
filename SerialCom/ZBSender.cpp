#include "ZBSender.h"

ZBSender::ZBSender(int aConnectionDescriptor, std::queue<ATCommandPacket> * aATCommandPacketQueue, std::mutex * aATCommandPacketMutex, std::condition_variable * aATCommandPacketCV) : connectionDescriptor(aConnectionDescriptor), ATCommandPacketQueue(aATCommandPacketQueue), ATCommandPacketMutex(aATCommandPacketMutex), ATCommandPacketCV(aATCommandPacketCV)
{
	std::cout << "ZBSender(int aConnectionDescriptor)" << std::endl;
}


void ZBSender::operator() ()
{
	while(true)
	{
		std::unique_lock<std::mutex> lu(*ATCommandPacketMutex);
		auto mySelf = this;
		ATCommandPacketCV->wait(lu, [&mySelf]{return !mySelf->ATCommandPacketQueue->empty();});
		while(!ATCommandPacketQueue->empty())
		{
			std::cout << "sending ATCommandPacket: " << ATCommandPacketQueue->front() << std::endl;
			write(connectionDescriptor, (void*) ATCommandPacketQueue->front().getEncodedPacket().data(), ATCommandPacketQueue->front().getEncodedPacket().size());
			fsync(connectionDescriptor);

			ATCommandPacketQueue->pop();
		}
	}

}