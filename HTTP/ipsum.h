#ifndef IPSUM_H
#define IPSUM_H
#include <mutex>
#include <condition_variable>
#include "../packet.h"
#include "../packetqueue.h"
#include <string>
#include <iostream>
#include <queue>

class Ipsum
{
	private:
	std::mutex * mainConditionVariableMutex, * ipsumConditionVariableMutex;
	std::condition_variable * mainConditionVariable, * ipsumConditionVariable;
	PacketQueue * ipsumSendQueue, * ipsumReceiveQueue;
	std::queue<Packet *> * localIpsumSendQueue;
	Ipsum(const Ipsum&);
	public:
	Ipsum(PacketQueue * ipsumSendQueue, PacketQueue * ipsumReceiveQueue, std::mutex * mainConditionVariableMutex, std::condition_variable * mainConditionVariable, std::mutex * ipsumConditionVariableMutex, std::condition_variable * ipsumConditionVariable);
	~Ipsum();
	void operator() ();
};

#endif
