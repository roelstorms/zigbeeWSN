#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <fcntl.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <boost/thread.hpp>
#include "./SerialCom/ZBReceiver.h"
#include "./SerialCom/ZBSender.h"
#include "./SerialCom/connection.h"
#include "./SerialCom/packets/libeliopacket.h"
#include "./SerialCom/packets/libeladdnodepacket.h"

#include "./HTTP/http.h"
#include "packetqueue.h"
#include "./webservice/webservice.h"
#include <thread>
#include "./HTTP/ipsum.h"
#include <ctime>
#include <typeinfo>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/Wrapper4InputSource.hpp>

class MainClass
{
	private:
	Http * socket;
	
	PacketQueue * zbReceiveQueue, * zbSenderQueue, * wsQueue, * ipsumSendQueue, * ipsumReceiveQueue;
	std::queue<Packet *> * localZBReceiveQueue, * localWSQueue, * localIpsumSendQueue, * localIpsumReceiveQueue;

	std::condition_variable * mainConditionVariable, * ipsumConditionVariable, * zbSenderConditionVariable;
	std::mutex * conditionVariableMutex, * ipsumConditionVariableMutex, * zbSenderConditionVariableMutex;

	Connection * con;

	boost::thread * zbReceiverThread, * zbSenderThread, * ipsumThread;
	ZBReceiver * zbReceiver;
	ZBSender * zbSender;
	Webservice * webService;
	Ipsum * ipsum;

	std::queue<std::pair<Packet *, time_t >> * packetsWaitingForResponse;
	
	void requestIOHandler(WSPacket * wsPacket);
	void changeFrequencyHandler(WSPacket * wsPacket);
	void addNodeHandler(WSPacket * wsPacket);
	void addSensorHandler(WSPacket * wsPacket);
	void RequestIOHandler(WSPacket * wsPacket);
	public:
	MainClass(int argc, char * argv[]);
	~MainClass();
	void operator () ();

	void libelIOHandler(Packet * packet);
	void webserviceHandler(Packet * packet);
	std::string findFieldInXML(std::string fieldName, std::string data);

};

#endif
