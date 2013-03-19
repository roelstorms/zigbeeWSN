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

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/insert_linebreaks.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <boost/archive/iterators/remove_whitespace.hpp>

#include "../errors.h"

class XML
{
	private:
	xercesc::DOMImplementation *impl; 

	/*
   	 *	Give the top node of the DOM tree you want to serialize and XML code will be returned.
	 */	 
	std::string serializeDOM(xercesc::DOMNode * node);

	public:
	XML();
	~XML();

	std::string uploadData(const std::string& type, const std::vector<std::pair<std::string, double>>& input);

	std::string createNewInstallation(const std::string& nameValue, const std::string& descriptionValue, const std::string& inuseValue);
	std::string createNewSensorGroup(const std::string& installationIDValue, const std::string& nameValue, const std::string& descriptionValue, const std::string& inuseValue); 
	std::string createNewSensor(const std::string& sensorGroupIDValue, const std::string& nameValue, const std::string& dataNameValue, const std::string& descriptionValue, const std::string& inuseValue);

	/*
	 *	Creates XML that generates a new type on the ipsum server. You can specify the name of this new type and several different field. 
	 *	Each field has a name and a type (for instance float_n or int_ or text (see ipsum documentation for the different types possible)
	 *
	 */
	std::string createNewType(const std::string& aName, const std::vector<std::pair<std::string, std::string>>& aListOfFields) throw (UnknownDataType);		
	std::string createNewUser();

	std::string login(const std::string& username, const std::string& password);

	/*
	 *	Reply is filename where the XML returned from ipsum on a login request is stored.
	 *	Function returns token needed by ipsum for requests which required to be logged in.
	 */
	std::string analyzeLoginReply(const std::string& reply);

	/*
	 *	Generates XML needed by the ipsum POST request to do a select.
	 *	No possibility to apply functions or name as or where which are all supported by ipsum.
	 *	TODO: test new implementation 
	 */
	std::string selectData(const std::vector<std::string>& fields, const std::string& startTime, const std::string& endTime);

	/*
	 *	analyzeSelect analyzes the ipsum XML response on a select call.
	 *	Returns a list of pairs where pair.first is the fieldname and pair.second is the value
	 *
	 */
	std::vector<std::pair<std::string, std::string>> analyzeSelect(const std::string& input);

	/*
	 * 	getTimestamp returns a timestamp in the format YYYY-DD-MMThh:mm:ss
	 */
	std::string getTimestamp(int houres, int minutes, int seconds, int day, int month, int year);

	/*
	 *	Does the same as getTimestamp but for the current time
	 */
	std::string getCurrentTimestamp();
};

#endif
