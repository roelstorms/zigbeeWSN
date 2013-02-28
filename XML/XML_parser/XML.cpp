#include "XML.h"
XML::XML()
{
	try {
	 	xercesc::XMLPlatformUtils::Initialize();
	 }
	 catch (const xercesc::XMLException& toCatch) {
	 	// Do your failure processing here
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
        xercesc::DOMImplementation *impl = xercesc::DOMImplementationRegistry::getDOMImplementation(tempStr);
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

        theOutput->release();
        theSerializer->release();
        return XMLOutput;
    }

std::string XML::uploadData(std::string type, std::vector<std::pair<std::string, double>> input)	// need to accept multiple arguments (pairs of field names and values)
{

	XMLCh tempStr[100];

	std::string XMLOutput;

        std::cout << "begin of upload" << std::endl;
        xercesc::XMLString::transcode("impl", tempStr, 99);
        xercesc::DOMImplementation* impl = xercesc::DOMImplementation::getImplementation();


        xercesc::XMLString::transcode("doc", tempStr, 99);
        xercesc::DOMDocument* doc = impl->createDocument(0, tempStr, 0);
	xercesc::DOMElement* docElement = doc->getDocumentElement();

        xercesc::XMLString::transcode("upload", tempStr, 99);
        xercesc::DOMElement* upload = doc->createElement(tempStr);
        docElement->appendChild(upload);


        std::cout << "mid of upload" << std::endl;
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
		//field1->setNodeValue(XMLString::transcode("test"));//, XMLString::transcode("0.12"));
		myType->appendChild(field);

		std::ostringstream stream;		// Can use boost to convert double to string more elegantly
		stream << (*it).second;
		std::string fieldValue = stream.str();
		
		xercesc::XMLString::transcode(fieldValue.c_str(), tempStr, 99);
		xercesc::DOMText* fieldvalue = doc->createTextNode(tempStr);
		//field1->setNodeValue(field1value);//, XMLString::transcode("0.12"));
		field->appendChild(fieldvalue);
	}

     	xercesc::XMLString::transcode("utimestamp", tempStr, 99);
        xercesc::DOMElement* utimestamp = doc->createElement(tempStr);
        myType->appendChild(utimestamp);  

	xercesc::XMLString::transcode("0", tempStr, 99);
        xercesc::DOMText* timestampValue = doc->createTextNode(tempStr);
	utimestamp->appendChild(timestampValue);
        std::cout << "end of upload" << std::endl;
	
	XMLOutput = serializeDOM(upload);
  	// Other terminations and cleanup.
	return XMLOutput;
}

std::string XML::createNewType(std::string name)
{
	std::string XMLOutput;
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

        xercesc::XMLString::transcode("impl", tempStr, 99);
        xercesc::DOMImplementation* impl = xercesc::DOMImplementation::getImplementation();

	std::cout << "XML::login mid" << std::endl;
        
	xercesc::XMLString::transcode("doc", tempStr, 99);
        impl->createDocument(0, tempStr, 0);
	xercesc::DOMDocument* doc = impl->createDocument();
         
       
	xercesc::XMLString::transcode("UserLogin", tempStr, 99);
        xercesc::DOMElement* userLoginNode = doc->createElement(tempStr);
        doc->appendChild(userLoginNode);

        xercesc::XMLString::transcode("password", tempStr, 99);
        xercesc::DOMElement* passwordNode = doc->createElement(tempStr);
        userLoginNode->appendChild(passwordNode);

	xercesc::XMLString::transcode(password.c_str(), tempStr, 99);
	xercesc::DOMText* passwordValue = doc->createTextNode(tempStr);
	passwordNode->appendChild(passwordValue);

        xercesc::XMLString::transcode("username", tempStr, 99);
        xercesc::DOMElement* usernameNode = doc->createElement(tempStr);
	userLoginNode->appendChild(usernameNode);

	xercesc::XMLString::transcode(username.c_str(), tempStr, 99);
	xercesc::DOMText* usernameValue = doc->createTextNode(tempStr);
	usernameNode->appendChild(usernameValue);
	
	XMLOutput = serializeDOM(userLoginNode);

	std::cout << "XML::login end" << std::endl;
	return 0;
}


std::string XML::analyzeLoginReply( std::string fileName)
{
	std::cout << "XML::analyzeLoginReply() begin" << std::endl;

	std::string token;
	
	XMLCh tempStr[100];
	xercesc::XMLString::transcode("impl", tempStr, 99);

        xercesc::DOMImplementation* impl = xercesc::DOMImplementation::getImplementation();
	xercesc::DOMLSParser       *parser = ((xercesc::DOMImplementationLS*)impl)->createLSParser(xercesc::DOMImplementationLS::MODE_SYNCHRONOUS, 0);
//	xercesc::DOMConfiguration  *config = parser->getDomConfig();
	xercesc::DOMDocument *doc;

	//config->setParameter(xercesc::XMLUni::fgDOMNamespaces, doNamespaces);
	//config->setParameter(xercesc::XMLUni::fgXercesSchema, doSchema);
	//config->setParameter(xercesc::XMLUni::fgXercesHandleMultipleImports, true);
	//config->setParameter(xercesc::XMLUni::fgXercesSchemaFullChecking, schemaFullChecking);	

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



	std::cout << "XML::analyzeLoginReply() end" << std::endl;
	return token;

}
