#ifndef ZBSENDER_H
#define ZBSENDER_H

#include <boost/thread/mutex.hpp>
#include <queue>
#include "../packetqueue.h"
#include <mutex>
#include <condition_variable>
#include "packets/libelchangefreqpacket.h"
#include "packets/libelchangenodefreqpacket.h"
#include "packets/libeladdnodepacket.h"
#include "packets/libelrequestiopacket.h"
#include <typeinfo>

class ZBSender
{
	private:
	int fileDescriptor;
	std::mutex  * zbSenderConditionVariableMutex;
	std::condition_variable * zbSenderConditionVariable;
	PacketQueue * zbSendQueue;	


	public:
	ZBSender(int fd, std::mutex * zbSenderConditionVariableMutex, std::condition_variable * zbSenderConditionVariable, PacketQueue * zbSendQueue);
	void operator () ();


};

#endif
