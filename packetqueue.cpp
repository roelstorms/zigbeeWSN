#include "packetqueue.h"

PacketQueue::PacketQueue() 
{

}

void PacketQueue::addPacket(Packet * aPacket) throw (InvalidPacketType)
{
	std::lock_guard<std::mutex> lg(mutex);
	queue.push(aPacket);

}

bool PacketQueue::empty() 
{
	std::lock_guard<std::mutex> lg(mutex);
	return queue.empty();
}

Packet * PacketQueue::getPacket() 
{
	std::lock_guard<std::mutex> lg(mutex);

	Packet * output = queue.front();
	queue.pop();
	return output;
}
