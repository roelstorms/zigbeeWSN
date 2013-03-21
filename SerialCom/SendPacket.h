#ifndef SENDPACKET_H
#define SENDPACKET_H

#include <boost/thread/mutex.hpp>
#include <queue>
#include "ATCommandPacket.h"
#include <mutex>
#include <condition_variable>

class SendPacket
{
	private:
	int connectionDescriptor;
	std::queue<ATCommandPacket> * ATCommandPacketQueue;	
	std::mutex * ATCommandPacketMutex;
	std::condition_variable * ATCommandPacketCV;
	public:
	SendPacket(int aConnectionDescriptor, std::queue<ATCommandPacket> * aATCommandPacketQueue, std::mutex * aATCommandPacketMutex, std::condition_variable * aATCommandPacketCV);
	void operator () ();

};

#endif
