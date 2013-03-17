#ifndef SENDPACKET_H
#define SENDPACKET_H

#include <boost/thread/mutex.hpp>
#include <queue>
#include "ATCommandPacket.h"

class SendPacket
{
	private:
	int connectionDescriptor;
	std::queue<ATCommandPacket> * ATCommandPacketQueue;	
	boost::mutex * ATCommandPacketMutex;

	public:
	SendPacket(int aConnectionDescriptor, std::queue<ATCommandPacket> * aATCommandPacketQueue, boost::mutex * aATCommandPacketMutex);
	void operator () ();

};

#endif
