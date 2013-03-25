#include "packetqueue.h"

PacketQueue::PacketQueue(std::condition_variable * aConditionVariable, std::mutex * aConditionVariableMutex) : conditionVariable (aConditionVariable), conditionVariableMutex(aConditionVariableMutex)
{

}

PacketQueue::addPacket(Packet * packet)
{
		std::lock_guard<std::mutex> lg(mutex);
		dataIOPacketQueue->push(packet);
		conditionVariable->notify_all();
}
