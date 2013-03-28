#include "ipsumuploadpacket.h"


IpsumUploadPacket::IpsumUploadPacket(int installationID, int sensorGroupID, std::vector<std::tuple<SensorType, int, float>> data) : IpsumPacket(IPSUM_UPLOAD), installationID(installationID), sensorGroupID(sensorGroupID), data(data)
{


}

int IpsumUploadPacket::getInstallationID() const
{
	return installationID;
}

int IpsumUploadPacket::getSensorGroupID() const
{
	return sensorGroupID;
}

const std::vector<std::pair<SensorType,float>>& IpsumUploadPacket::getData() const
{
	return data;
}
