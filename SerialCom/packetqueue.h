#ifndef PACKETQUEUE_H
#define PACKETQUEUE_H

#include <mutex>
#include "packet.h"
#include <queue>
#include <condition_variable>
#include "dataIOPacket.h"
#include "errors.h"

class PacketQueue
{
	private:
		std::mutex mutex;
		std::mutex * conditionVariableMutex;
		std::condition_variable * conditionVariable;
		std::queue<Packet *> packetQueue;	
		PacketQueue(PacketQueue&);
		PacketQueue(const PacketQueue&);
		PacketQueue& operator=(const PacketQueue&);

	public:
		PacketQueue(std::condition_variable * aConditionVariable, std::mutex * aConditionVariableMutex);
		void addPacket(Packet * aPacket); throw (InvalidPacketType);
};

#endif
