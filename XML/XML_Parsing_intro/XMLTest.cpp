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
#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <string>
#include <iostream>

// Other include files, declarations, and non-Xerces-C++ initializations.
using namespace std;
using namespace xercesc;

int serializeDOM(DOMNode* node) {

        XMLCh tempStr[100];
        XMLString::transcode("LS", tempStr, 99);
        DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(tempStr);
        DOMLSSerializer* theSerializer = ((DOMImplementationLS*)impl)->createLSSerializer();

        // optionally you can set some features on this serializer
        if (theSerializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTDiscardDefaultContent, true))
            theSerializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTDiscardDefaultContent, true);

        if (theSerializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true))
             theSerializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);

        // optionally you can implement your DOMErrorHandler (e.g. MyDOMErrorHandler)
        // and set it to the serializer
        //DOMErrorHandler* myErrorHandler() = new myDOMErrorHandler();
        //theSerializer->getDomConfig()->setParameter(XMLUni::fgDOMErrorHandler, myErrorHandler);

        // StdOutFormatTarget prints the resultant XML stream
        // to stdout once it receives any thing from the serializer.
        XMLFormatTarget *myFormTarget = new StdOutFormatTarget();
        DOMLSOutput* theOutput = ((DOMImplementationLS*)impl)->createLSOutput();
        theOutput->setByteStream(myFormTarget);
	theSerializer->writeToString(node);
        try {
            // do the serialization through DOMLSSerializer::write();
            theSerializer->write(node, theOutput);
        }
        catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cout << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return -1;
        }
        catch (const DOMException& toCatch) {
            char* message = XMLString::transcode(toCatch.msg);
            cout << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return -1;
        }
        catch (...) {
            cout << "Unexpected Exception \n" ;
            return -1;
        }

        theOutput->release();
        theSerializer->release();
        return 0;
    }


int main(int argc, char* argv[])
{

  	try
       	{
    		XMLPlatformUtils::Initialize();
 	}
  	catch (const XMLException& toCatch) 
	{
    		// Do your failure processing here
    		return 1;
  	}

  // Do your actual work with Xerces-C++ here.

	XMLCh tempStr[100];

        XMLString::transcode("Range", tempStr, 99);
        DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(tempStr);

        XMLString::transcode("upload", tempStr, 99);
        DOMDocument* doc = impl->createDocument(0, tempStr, 0);
        DOMElement* upload = doc->getDocumentElement();

        XMLString::transcode("items", tempStr, 99);
        DOMElement* items = doc->createElement(tempStr);
        upload->appendChild(items);

        XMLString::transcode("myType", tempStr, 99);
        DOMElement* myType = doc->createElement(tempStr);
        items->appendChild(myType);

        XMLString::transcode("field1", tempStr, 99);
        DOMNode* field1 = doc->createElement(tempStr);
	//field1->setNodeValue(XMLString::transcode("test"));//, XMLString::transcode("0.12"));
        myType->appendChild(field1);

	XMLString::transcode("1.2", tempStr, 99);
        DOMText* field1value = doc->createTextNode(tempStr);
	//field1->setNodeValue(field1value);//, XMLString::transcode("0.12"));
	field1->appendChild(field1value);



        XMLString::transcode("field2", tempStr, 99);
        DOMElement* field2 = doc->createElement(tempStr);
        myType->appendChild(field2);

     	XMLString::transcode("utimestamp", tempStr, 99);
        DOMElement* utimestamp = doc->createElement(tempStr);
        myType->appendChild(utimestamp);  

        //XMLString::transcode("aTextNode", tempStr, 99);
        //DOMText* textNode = doc->createTextNode(tempStr);
        //e1->appendChild(textNode);
	printf("%s\n", (char*) tempStr + 4);
	std::cout << XMLString::transcode(tempStr) << std::endl;
        // optionally, call release() to release the resource associated with the range after done
	
	serializeDOM(upload);


	DOMRange* range = doc->createRange();
        range->release();



        // removedElement is an orphaned node, optionally call release() to release associated resource
        //DOMNode* removedElement = root->removeChild(e2);
        //removedElement->release();

        // no need to release this returned object which is owned by implementation
        XMLString::transcode("*", tempStr, 99);
        DOMNodeList*    nodeList = doc->getElementsByTagName(tempStr);

        // done with the document, must call release() to release the entire document resources
        doc->release();
  
	XMLPlatformUtils::Terminate();

  // Other terminations and cleanup.
  return 0;
}

