#ifndef IPSUMUPLOADPACKET_H
#define IPSUMUPLOADPACKET_H
#include "../mainclass.h"
#include <vector>
#include "ipsumpacket.h"

class IpsumUploadPacket : public IpsumPacket
{
	private:
	int installationID, sensorGroup;
	std::vector<std::pair<SensorType, float>> data;
	public:
	IpsumUploadPacket(int installationID, int sensorGroup, std::vector<std::pair<SensorType, float>> data);

};

#endif
