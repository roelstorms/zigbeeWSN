#ifndef LIBELIUMIOPACKET_H
#define LIBELIUMIOPACKET_H

#define CREATESENSORGETTER(name, sensortype) float name() const throw(DataNotAvailable)\
{\
	auto it = sensorData.find(sensortype); \
	if(it == sensorData.end())\
	{\
		throw DataNotAvailable(); \
	}\
	return it->second;\
}




#include <string>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include "datapacket.h"
#include <iomanip>
#include <map>
#include "../errors.h"

enum SensorType
{
	PLUVIO, VANE, ANEMO, CO2, BAT, PRES, HUM, TEMP 
};

class LibeliumIOPacket : public DataPacket
{
	private:
		unsigned char nodeIdentifier;
		std::map<SensorType, float> sensorData;
	public:
		LibeliumIOPacket(std::vector<unsigned char> input);
		unsigned char getNodeIdentifier() const;
	 	
		CREATESENSORGETTER(getTemperature, TEMP)		//Macro to generate setters for all the sensor types	
		CREATESENSORGETTER(getHumidity, HUM)	
		CREATESENSORGETTER(getPressure, PRES)	
		CREATESENSORGETTER(getBattery, BAT)	
		CREATESENSORGETTER(getCO2, CO2)	
		CREATESENSORGETTER(getAnemo, ANEMO)	
		CREATESENSORGETTER(getVane, VANE)
		CREATESENSORGETTER(getPluvio, PLUVIO)



};

#endif
