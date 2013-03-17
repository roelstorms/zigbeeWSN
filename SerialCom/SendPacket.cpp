#include "SendPacket.h"

SendPacket::SendPacket(int aConnectionDescriptor, std::queue<ATCommandPacket> * aATCommandPacketQueue, boost::mutex * aATCommandPacketMutex) : connectionDescriptor(aConnectionDescriptor), ATCommandPacketQueue(aATCommandPacketQueue), ATCommandPacketMutex(aATCommandPacketMutex)
{
	std::cout << "SendPacket(int aConnectionDescriptor)" << std::endl;
}


void SendPacket::operator() ()
{
	while(true)
	{
		try
		{
			ATCommandPacketMutex->lock();
			
		}
		catch(boost::thread_resource_error)
		{
			std::cerr << "ATCommandPacketMutex could not be locked so the read in data packed wasn't stored in dataIOPacketQueue. \nPacked lost: " <<  std::endl;
			continue;
		}

		while(!ATCommandPacketQueue->empty())
		{
			std::cout << "sending ATCommandPacket: " << ATCommandPacketQueue->front() << std::endl;
			write(connectionDescriptor, (void*) ATCommandPacketQueue->front().getEncodedPacket().data(), ATCommandPacketQueue->front().getEncodedPacket().size());
			fsync(connectionDescriptor);

			ATCommandPacketQueue->pop();
		}
		ATCommandPacketMutex->unlock();
	}

}
