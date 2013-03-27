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
#include "./SerialCom/connection.h"
#include "./SerialCom/libeliopacket.h"
#include "./HTTP/http.h"
#include "packetqueue.h"
#include "./webservice/webservice.h"
#include <thread>

class MainClass
{
	private:
	Http * socket;
	
	PacketQueue * zbSendQueue, * wsQueue;
	std::queue<Packet *> * localZBSendQueue;

	std::condition_variable * mainConditionVariable;
	std::mutex * conditionVariableMutex;

	Connection * con;

	boost::thread * zbReceiverThread;
	public:
	MainClass(int argc, char * argv[]);
	~MainClass();
	void operator () ();

	void libelIOHandler(Packet * packet);

};

#endif
