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

#include <sstream>
class XML
{
	private:
	

	public:
	XML();
	~XML();
	int serializeDOM(xercesc::DOMNode * node);
	int uploadData(std::string type, std::vector<std::pair<std::string, double>> input);
	int createNewType(std::string name);
	int createNewUser();
	int login(std::string username, std::string password);
	std::string analyzeLoginReply( std::string reply);
	


};

#endif
