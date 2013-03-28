#ifndef ZBSENDER_H
#define ZBSENDER_H

#include <boost/thread/mutex.hpp>
#include <queue>
#include "../packetqueue.h"
#include <mutex>
#include <condition_variable>

class ZBSender
{
	private:
	int fileDescriptor;
	PacketQueue * zbSendQueue;	
	std::mutex  * zbSenderConditionVariableMutex;
	std::condition_variable * zbSenderConditionVariable;
	public:
	ZBSender(int fd, std::mutex * zbSenderConditionVariableMutex, std::condition_variable * zbSenderConditionVariable, PacketQueue * zbSendQueue);
	void operator () ();
};

#endif
