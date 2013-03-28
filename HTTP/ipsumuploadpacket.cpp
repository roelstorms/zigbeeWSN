#include "ipsumuploadpacket.h"


IpsumUploadPacket::IpsumUploadPacket(int installationID, int sensorGroup, std::vector<std::pair<SensorType, float>> data) : IpsumPacket(IPSUM_UPLOAD)
{


}

