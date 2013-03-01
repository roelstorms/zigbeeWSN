#ifndef XML_H
#define XML_H

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMRange.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/dom/DOMLSSerializerFilter.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/dom/DOMLSParser.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <sys/time.h>
#include <sstream>
#include <stdlib.h>

class XML
{
	private:
	xercesc::DOMImplementation *impl; 

	public:
	XML();
	~XML();
	std::string serializeDOM(xercesc::DOMNode * node);
	std::string uploadData(std::string type, std::vector<std::pair<std::string, double>> input);
	std::string createNewType(std::string nameValue, std::string typeValue);
	std::string createNewUser();
	std::string login(std::string username, std::string password);
	std::string analyzeLoginReply( std::string reply);
	std::string createNewInstallation(std::string nameValue, std::string descriptionValue, std::string inuseValue);
	std::string createNewSensorGroup(std::string installationIDValue, std::string nameValue, std::string descriptionValue, std::string inuseValue); 
	std::string createNewSensor(std::string sensorGroupIDValue, std::string nameValue, std::string descriptionValue, std::string inuseValue);
};

#endif
