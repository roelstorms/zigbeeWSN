nclude "XML.h"
XML::XML()
{
	std::cout << "XML constructor" << std::endl << std::endl;
	try {
		xercesc::XMLPlatformUtils::Initialize();
	}
	catch (const xercesc::XMLException& toCatch) {
		std::cout << "xercesc::XMLPlatformUtils::Initialize() failed" << std::endl << std::endl;// Do your failure processing here
	}

	XMLCh tempStr[100];
	xercesc::XMLString::transcode("Core", tempStr, 99);
	impl = xercesc::DOMImplementationRegistry::getDOMImplementation(tempStr);
	if(impl == NULL)
	{
		std::cout << "no implementation found" << std::endl;
	}

}

XML::~XML()
{
	xercesc::XMLPlatformUtils::Terminate();
}


std::string XML::serializeDOM(xercesc::DOMNode* node) {

	XMLCh tempStr[100];
	std::string XMLOutput;

	xercesc::XMLString::transcode("LS", tempStr, 99);
	xercesc::DOMLSSerializer* theSerializer = ((xercesc::DOMImplementationLS*)impl)->createLSSerializer();

	// optionally you can set some features on this serializer
	if (theSerializer->getDomConfig()->canSetParameter(xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true))
		theSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMWRTDiscardDefaultContent, true);

	if (theSerializer->getDomConfig()->canSetParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true))
		theSerializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);

	// optionally you can implement your DOMLSSerializerFilter (e.g. MyDOMLSSerializerFilter)
	// and set it to the serializer
	//DOMLSSerializerFilter* myFilter = new myDOMLSSerializerFilter();
	//theSerializer->setFilter(myFilter);

	// optionally you can implement your DOMErrorHandler (e.g. MyDOMErrorHandler)
	// and set it to the serializer
	//DOMErrorHandler* myErrorHandler() = new myDOMErrorHandler();
	//theSerializer->getDomConfig()->setParameter(XMLUni::fgDOMErrorHandler, myErrorHandler);

	// StdOutFormatTarget prints the resultant XML stream
	// to stdout once it receives any thing from the serializer.

	xercesc::XMLFormatTarget *myFormTarget = new xercesc::StdOutFormatTarget();
	xercesc::DOMLSOutput* theOutput = ((xercesc::DOMImplementationLS*)impl)->createLSOutput();
	theOutput->setByteStream(myFormTarget);
	XMLOutput = xercesc::XMLString::transcode(theSerializer->writeToString(node));
	try {
		// do the serialization through DOMLSSerializer::write();
		theSerializer->write(node, theOutput);
	}
	catch (const xercesc::XMLException& toCatch) {
		char* message = xercesc::XMLString::transcode(toCatch.getMessage());
		std::cout << "Exception message is: \n"
			<< message << "\n";
		xercesc::XMLString::release(&message);
	}
	catch (const xercesc::DOMException& toCatch) {
		char* message = xercesc::XMLString::transcode(toCatch.msg);
		std::cout << "Exception message is: \n"
			<< message << "\n";
		xercesc::XMLString::release(&message);
	}
	catch (...) {
		std::cout << "Unexpected Exception \n" ;
	}
	delete myFormTarget;
	theOutput->release();
	theSerializer->release();
	return XMLOutput;
}

std::string XML::uploadData(std::string type, std::vector<std::pair<std::string, double>> input)	// need to accept multiple arguments (pairs of field names and values)
{
	XMLCh tempStr[100];

	std::string XMLOutput;

	std::cout << "begin of upload" << std::endl;

	xercesc::XMLString::transcode("upload", tempStr, 99);
	xercesc::DOMDocument* doc = impl->createDocument(0, tempStr, 0);
	xercesc::DOMElement* upload = doc->getDocumentElement();


	xercesc::XMLString::transcode("utimestamp", tempStr, 99);
	xercesc::DOMElement* utimestamp = doc->createElement(tempStr);
	upload->appendChild(utimestamp);  


	unsigned long int sec = time(NULL);
	std::cout << "time: " << std::endl << std::string(std::to_string(sec)) << std::endl;

	xercesc::XMLString::transcode(std::to_string(sec).c_str(), tempStr, 99);
	xercesc::DOMText* timestampValue = doc->createTextNode(tempStr);
	utimestamp->appendChild(timestampValue);

	xercesc::XMLString::transcode("items", tempStr, 99);
	xercesc::DOMElement* items = doc->createElement(tempStr);
	upload->appendChild(items);

	xercesc::XMLString::transcode(type.c_str(), tempStr, 99);
	xercesc::DOMElement* myType = doc->createElement(tempStr);
	items->appendChild(myType);

	for(auto it = input.begin(); it < input.end(); ++it)
	{		

		xercesc::XMLString::transcode((*it).first.c_str(), tempStr, 99);
		xercesc::DOMNode* field = doc->createElement(tempStr);
		myType->appendChild(field);

		std::ostringstream stream;		// Can use boost to convert double to string more elegantly
		stream << (*it).second;
		std::string fieldValue = stream.str();

		xercesc::XMLString::transcode(fieldValue.c_str(), tempStr, 99);
		xercesc::DOMText* fieldvalue = doc->createTextNode(tempStr);
		field->appendChild(fieldvalue);

		xercesc::XMLString::transcode("utimestamp", tempStr, 99);
		xercesc::DOMNode* fieldTimestamp = doc->createElement(tempStr);
		myType->appendChild(fieldTimestamp);

		xercesc::XMLString::transcode("0", tempStr, 99);
		xercesc::DOMText* fieldTimestampValue = doc->createTextNode(tempStr);
		fieldTimestamp->appendChild(fieldTimestampValue);

	}


	XMLOutput = serializeDOM(upload);
	// Other terminations and cleanup.
	return XMLOutput;
}

std::string XML::createNewInstallation(std::string nameValue, std::string descriptionValue, std::string inuseValue)
{
	XMLCh tempStr[100];

	std::string XMLOutput;

	std::cout << "begin of createNewInstallation" << std::endl;

	xercesc::XMLString::transcode("doc", tempStr, 99);
	xercesc::DOMDocument* doc = impl->createDocument(0, tempStr, 0);
	xercesc::DOMElement* docElement = doc->getDocumentElement();

	xercesc::XMLString::transcode("Installation", tempStr, 99);
	xercesc::DOMElement* installation = doc->createElement(tempStr);
	docElement->appendChild(installation);

	xercesc::XMLString::transcode("start", tempStr, 99);
	xercesc::DOMElement* start = doc->createElement(tempStr);
	installation->appendChild(start);

	xercesc::XMLString::transcode("2013-02-28T14:48:29", tempStr, 99);
	xercesc::DOMText* startFieldValue = doc->createTextNode(tempStr);
	start->appendChild(startFieldValue);

	xercesc::XMLString::transcode("end", tempStr, 99);
	xercesc::DOMElement* end = doc->createElement(tempStr);
	installation->appendChild(end);

	xercesc::XMLString::transcode("0001-01-01T00:00:00", tempStr, 99);
	xercesc::DOMText* endFieldValue = doc->createTextNode(tempStr);
	end->appendChild(endFieldValue);

	xercesc::XMLString::transcode("id", tempStr, 99);
	xercesc::DOMElement* id = doc->createElement(tempStr);
	installation->appendChild(id);

	xercesc::XMLString::transcode("0", tempStr, 99);
	xercesc::DOMText* idFieldValue = doc->createTextNode(tempStr);
	id->appendChild(idFieldValue);

	xercesc::XMLString::transcode("name", tempStr, 99);
	xercesc::DOMElement* name = doc->createElement(tempStr);
	installation->appendChild(name);

	xercesc::XMLString::transcode(nameValue.c_str(), tempStr, 99);
	xercesc::DOMText* nameFieldValue = doc->createTextNode(tempStr);
	name->appendChild(nameFieldValue);

	xercesc::XMLString::transcode("description", tempStr, 99);
	xercesc::DOMElement* description = doc->createElement(tempStr);
	installation->appendChild(description);

	xercesc::XMLString::transcode(descriptionValue.c_str(), tempStr, 99);
	xercesc::DOMText* descriptionFieldValue = doc->createTextNode(tempStr);
	description->appendChild(descriptionFieldValue);

	xercesc::XMLString::transcode("inuse", tempStr, 99);
	xercesc::DOMElement* inuse = doc->createElement(tempStr);
	installation->appendChild(inuse);

	xercesc::XMLString::transcode(inuseValue.c_str(), tempStr, 99);
	xercesc::DOMText* inuseFieldValue = doc->createTextNode(tempStr);
	inuse->appendChild(inuseFieldValue);

	xercesc::XMLString::transcode("infoname", tempStr, 99);
	xercesc::DOMElement* infoname = doc->createElement(tempStr);
	installation->appendChild(infoname);

	XMLOutput = serializeDOM(installation);
	doc->release();
	return XMLOutput;
}

std::string XML::createNewSensorGroup(std::string installationIDValue, std::string nameValue, std::string descriptionValue, std::string inuseValue)
{

	XMLCh tempStr[100];

	std::string XMLOutput;

	std::cout << "begin of createNEwSensorGroup" << std::endl;

	xercesc::XMLString::transcode("doc", tempStr, 99);
	xercesc::DOMDocument* doc = impl->createDocument(0, tempStr, 0);
	xercesc::DOMElement* docElement = doc->getDocumentElement();

	xercesc::XMLString::transcode("SensorGroup", tempStr, 99);
	xercesc::DOMElement* sensorGroup = doc->createElement(tempStr);
	docElement->appendChild(sensorGroup);

	xercesc::XMLString::transcode("start", tempStr, 99);
	xercesc::DOMElement* start = doc->createElement(tempStr);
	sensorGroup->appendChild(start);

	unsigned long int sec = time(NULL);
	std::cout << "time: " << std::endl << std::string(std::to_string(sec)) << std::endl;
	xercesc::XMLString::transcode("2013-02-28T14:48:29", tempStr, 99);
	xercesc::DOMText* startFieldValue = doc->createTextNode(tempStr);
	start->appendChild(startFieldValue);

	xercesc::XMLString::transcode("end", tempStr, 99);
	xercesc::DOMElement* end = doc->createElement(tempStr);
	sensorGroup->appendChild(end);

	xercesc::XMLString::transcode("0001-01-01T00:00:00", tempStr, 99);
	xercesc::DOMText* endFieldValue = doc->createTextNode(tempStr);
	end->appendChild(endFieldValue);

	xercesc::XMLString::transcode("installationid", tempStr, 99);
	xercesc::DOMElement* installationid = doc->createElement(tempStr);
	sensorGroup->appendChild(installationid);

	xercesc::XMLString::transcode(installationIDValue.c_str(), tempStr, 99);
	xercesc::DOMText* installationidFieldValue = doc->createTextNode(tempStr);
	installationid->appendChild(installationidFieldValue);

	xercesc::XMLString::transcode("id", tempStr, 99);
	xercesc::DOMElement* id = doc->createElement(tempStr);
	sensorGroup->appendChild(id);

	xercesc::XMLString::transcode("0", tempStr, 99);
	xercesc::DOMText* idFieldValue = doc->createTextNode(tempStr);
	id->appendChild(idFieldValue);

	xercesc::XMLString::transcode("name", tempStr, 99);
	xercesc::DOMElement* name = doc->createElement(tempStr);
	sensorGroup->appendChild(name);

	xercesc::XMLString::transcode(nameValue.c_str(), tempStr, 99);
	xercesc::DOMText* nameFieldValue = doc->createTextNode(tempStr);
	name->appendChild(nameFieldValue);

	xercesc::XMLString::transcode("description", tempStr, 99);
	xercesc::DOMElement* description = doc->createElement(tempStr);
	sensorGroup->appendChild(description);

	xercesc::XMLString::transcode(descriptionValue.c_str(), tempStr, 99);
	xercesc::DOMText* descriptionFieldValue = doc->createTextNode(tempStr);
	description->appendChild(descriptionFieldValue);

	xercesc::XMLString::transcode("inuse", tempStr, 99);
	xercesc::DOMElement* inuse = doc->createElement(tempStr);
	sensorGroup->appendChild(inuse);

	xercesc::XMLString::transcode(inuseValue.c_str(), tempStr, 99);
	xercesc::DOMText* inuseFieldValue = doc->createTextNode(tempStr);
	inuse->appendChild(inuseFieldValue);

	xercesc::XMLString::transcode("infoname", tempStr, 99);
	xercesc::DOMElement* infoname = doc->createElement(tempStr);
	sensorGroup->appendChild(infoname);

	XMLOutput = serializeDOM(sensorGroup);
	doc->release();
	return XMLOutput;
}

std::string XML::createNewSensor(std::string sensorGroupIDValue, std::string nameValue, std::string dataNameValue, std::string descriptionValue, std::string inuseValue)
{

	XMLCh tempStr[100];

	std::string XMLOutput;

	std::cout << "begin of createNEwSensorGroup" << std::endl;

	xercesc::XMLString::transcode("doc", tempStr, 99);
	xercesc::DOMDocument* doc = impl->createDocument(0, tempStr, 0);
	xercesc::DOMElement* docElement = doc->getDocumentElement();

	xercesc::XMLString::transcode("Sensor", tempStr, 99);
	xercesc::DOMElement* sensor = doc->createElement(tempStr);
	docElement->appendChild(sensor);

	xercesc::XMLString::transcode("location", tempStr, 99);
	xercesc::DOMElement* location = doc->createElement(tempStr);
	sensor->appendChild(location);

	xercesc::XMLString::transcode("14.04", tempStr, 99);
	xercesc::DOMText* locationFieldValue = doc->createTextNode(tempStr);
	location->appendChild(locationFieldValue);

	xercesc::XMLString::transcode("sensorgroupid", tempStr, 99);
	xercesc::DOMElement* sensorgroupid = doc->createElement(tempStr);
	sensor->appendChild(sensorgroupid);

	xercesc::XMLString::transcode(sensorGroupIDValue.c_str(), tempStr, 99);
	xercesc::DOMText* sensorGroupFieldValue = doc->createTextNode(tempStr);
	sensorgroupid->appendChild(sensorGroupFieldValue);


	xercesc::XMLString::transcode("frequency", tempStr, 99);
	xercesc::DOMElement* frequency = doc->createElement(tempStr);
	sensor->appendChild(frequency);

	xercesc::XMLString::transcode("5", tempStr, 99);
	xercesc::DOMText* frequencyFieldValue = doc->createTextNode(tempStr);
	frequency->appendChild(frequencyFieldValue);

	xercesc::XMLString::transcode("dataname", tempStr, 99);
	xercesc::DOMElement* dataname = doc->createElement(tempStr);
	sensor->appendChild(dataname);

	xercesc::XMLString::transcode(dataNameValue.c_str(), tempStr, 99);
	xercesc::DOMText* datanameFieldValue = doc->createTextNode(tempStr);
	dataname->appendChild(datanameFieldValue);

	xercesc::XMLString::transcode("id", tempStr, 99);
	xercesc::DOMElement* id = doc->createElement(tempStr);
	sensor->appendChild(id);

	xercesc::XMLString::transcode("0", tempStr, 99);
	xercesc::DOMText* idFieldValue = doc->createTextNode(tempStr);
	id->appendChild(idFieldValue);

	xercesc::XMLString::transcode("name", tempStr, 99);
	xercesc::DOMElement* name = doc->createElement(tempStr);
	sensor->appendChild(name);

	xercesc::XMLString::transcode(nameValue.c_str(), tempStr, 99);
	xercesc::DOMText* nameFieldValue = doc->createTextNode(tempStr);
	name->appendChild(nameFieldValue);

	xercesc::XMLString::transcode("description", tempStr, 99);
	xercesc::DOMElement* description = doc->createElement(tempStr);
	sensor->appendChild(description);

	xercesc::XMLString::transcode(descriptionValue.c_str(), tempStr, 99);
	xercesc::DOMText* descriptionFieldValue = doc->createTextNode(tempStr);
	description->appendChild(descriptionFieldValue);

	xercesc::XMLString::transcode("inuse", tempStr, 99);
	xercesc::DOMElement* inuse = doc->createElement(tempStr);
	sensor->appendChild(inuse);

	xercesc::XMLString::transcode(inuseValue.c_str(), tempStr, 99);
	xercesc::DOMText* inuseFieldValue = doc->createTextNode(tempStr);
	inuse->appendChild(inuseFieldValue);

	xercesc::XMLString::transcode("infoname", tempStr, 99);
	xercesc::DOMElement* infoname = doc->createElement(tempStr);
	sensor->appendChild(infoname);

	XMLOutput = serializeDOM(sensor);
	doc->release();
	return XMLOutput;
}

std::string XML::createNewType(std::string aName, std::string aFieldName)
{
	std::string XMLOutput;
	XMLCh tempStr[100];
	std::cout << "begin of createNewType" << std::endl;

	xercesc::XMLString::transcode("doc", tempStr, 99);
	xercesc::DOMDocument* doc = impl->createDocument(0, tempStr, 0);
	xercesc::DOMElement* docElement = doc->getDocumentElement();

	xercesc::XMLString::transcode("usertype", tempStr, 99);
	xercesc::DOMElement* usertype = doc->createElement(tempStr);
	usertype->setAttribute(xercesc::XMLString::transcode("name"), xercesc::XMLString::transcode(aName.c_str()));
	docElement->appendChild(usertype);

	xercesc::XMLString::transcode("field", tempStr, 99);
	xercesc::DOMElement* field = doc->createElement(tempStr);
	usertype->appendChild(field);

	xercesc::XMLString::transcode("sql", tempStr, 99);
	xercesc::DOMElement* sql = doc->createElement(tempStr);
	field->appendChild(sql);

	xercesc::XMLString::transcode("type", tempStr, 99);
	xercesc::DOMElement* sqlType = doc->createElement(tempStr);
	sql->appendChild(sqlType);

	xercesc::XMLString::transcode("decimal_ps_", tempStr, 99);
	xercesc::DOMText* sqlTypeFieldValue = doc->createTextNode(tempStr);
	sqlType->appendChild(sqlTypeFieldValue);

	xercesc::XMLString::transcode("l1", tempStr, 99);
	xercesc::DOMElement* l1 = doc->createElement(tempStr);
	sql->appendChild(l1);

	xercesc::XMLString::transcode("5", tempStr, 99);
	xercesc::DOMText* l1FieldValue = doc->createTextNode(tempStr);
	l1->appendChild(l1FieldValue);

	xercesc::XMLString::transcode("l2", tempStr, 99);
	xercesc::DOMElement* l2 = doc->createElement(tempStr);
	sql->appendChild(l2);

	xercesc::XMLString::transcode("2", tempStr, 99);
	xercesc::DOMText* l2FieldValue = doc->createTextNode(tempStr);
	l2->appendChild(l2FieldValue);

	xercesc::XMLString::transcode("type", tempStr, 99);
	xercesc::DOMElement* type = doc->createElement(tempStr);
	field->appendChild(type);

	xercesc::XMLString::transcode("float", tempStr, 99);
	xercesc::DOMText* typeFieldValue = doc->createTextNode(tempStr);
	type->appendChild(typeFieldValue);

	xercesc::XMLString::transcode("name", tempStr, 99);
	xercesc::DOMElement* name = doc->createElement(tempStr);
	field->appendChild(name);

	xercesc::XMLString::transcode(aFieldName.c_str(), tempStr, 99);
	xercesc::DOMText* nameFieldValue = doc->createTextNode(tempStr);
	name->appendChild(nameFieldValue);

	XMLOutput = serializeDOM(usertype);
	doc->release();

	return XMLOutput;
}

std::string XML::createNewUser()
{
	std::string XMLOutput;
	return XMLOutput;
}

std::string XML::login(std::string username, std::string password)
{
	std::cout << "XML::login begin" << std::endl;
	std::string XMLOutput;
	XMLCh tempStr[100];

	std::cout << "XML::login mid" << std::endl;

	xercesc::XMLString::transcode("doc", tempStr, 99);
	impl->createDocument(0, tempStr, 0);
	xercesc::DOMDocument* doc = impl->createDocument();

	xercesc::XMLString::transcode("UserLogin", tempStr, 99);
	xercesc::DOMElement* userLoginNode = doc->createElement(tempStr);
	doc->appendChild(userLoginNode); 

	xercesc::XMLString::transcode("username", tempStr, 99);
	xercesc::DOMElement* usernameNode = doc->createElement(tempStr);
	userLoginNode->appendChild(usernameNode);

	xercesc::XMLString::transcode(username.c_str(), tempStr, 99);
	xercesc::DOMText* usernameValue = doc->createTextNode(tempStr);
	usernameNode->appendChild(usernameValue);

	xercesc::XMLString::transcode("password", tempStr, 99);
	xercesc::DOMElement* passwordNode = doc->createElement(tempStr);
	userLoginNode->appendChild(passwordNode);

	xercesc::XMLString::transcode(password.c_str(), tempStr, 99);
	xercesc::DOMText* passwordValue = doc->createTextNode(tempStr);
	passwordNode->appendChild(passwordValue);

	XMLOutput = serializeDOM(userLoginNode);

	std::cout << "XML::login end" << std::endl;
	return XMLOutput;
}

std::string XML::analyzeLoginReply( std::string fileName)
{
	std::cout << "XML::analyzeLoginReply() begin" << std::endl;

	std::string token;

	XMLCh tempStr[100];

	//xercesc::XMLString::transcode("impl", tempStr, 99);
	//xercesc::DOMImplementation* impl = xercesc::DOMImplementation::getImplementation();

	xercesc::DOMLSParser *parser = ((xercesc::DOMImplementationLS*)impl)->createLSParser(xercesc::DOMImplementationLS::MODE_SYNCHRONOUS, 0);
	//	xercesc::DOMConfiguration  *config = parser->getDomConfig();
	xercesc::DOMDocument *doc;

	//config->setParameter(xercesc::XMLUni::fgDOMNamespaces, doNamespaces);
	//config->setParameter(xercesc::XMLUni::fgXercesSchema, doSchema);
	//config->setParameter(xercesc::XMLUni::fgXercesHandleMultipleImports, true);
	//config->setParameter(xercesc::XMLUni::fgXercesSchemaFullChecking, schemaFullChecking);	
	std::cout << "filename of log.txt: " << fileName << std::endl;
	doc = parser->parseURI(fileName.c_str());
	xercesc::DOMElement * docElement = doc->getDocumentElement();	
	std::cout << "docElement count: " << docElement->getChildElementCount () << std::endl;
	//for(int i = 0; i < docElement->getChildElementCount(); ++i)
	xercesc::DOMElement * nextElement;
	nextElement = docElement->getFirstElementChild();
	while(nextElement != NULL)
	{
		//std::cout << "element name: " <<  xercesc::XMLString::transcode(nextElement->getTagName()) << std::endl;
		if(xercesc::XMLString::compareIString(nextElement->getTagName(), xercesc::XMLString::transcode("token")) == 0)
		{
			//std::cout << "nextelement has children" << std::endl << xercesc::XMLString::transcode(nextElement->getTextContent()) << std::endl;
			token = std::string(xercesc::XMLString::transcode(nextElement->getTextContent()));

		}
		else if(xercesc::XMLString::compareIString(nextElement->getTagName(), xercesc::XMLString::transcode("error")) == 0)
		{
			if(std::string(xercesc::XMLString::transcode(nextElement->getTextContent())) == std::string("True"))
			{
				//std::cout << "Error occured in receiving the token" << std::endl;
				token = nullptr;
			}

		}
		nextElement = nextElement->getNextElementSibling();
	}	


	std::cout << "token: " << token << std::endl;
	std::cout << "XML::analyzeLoginReply() end" << std::endl;
	return token;

}
