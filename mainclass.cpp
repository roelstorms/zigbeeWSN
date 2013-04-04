#include "mainclass.h"

MainClass::MainClass(int argc, char * argv[])
{
	int user = getuid();
	if (user != 0)
	{
		std::cerr << "root privileges needed" << std::endl;
		throw NoRoot(); 
	}
	
	socket = new Http("http://ipsum.groept.be");

/*	
	try
	{
		socket->ipsumInfo();
	}
	catch(HttpError)
	{
		std::cerr << "Could not connect to Ipsum" << std::endl;
		//return 1;
	}
*/
	
	std::cout << "argc: " << argc << std::endl;
	if(argc != 2)
	{
		std::cerr << "also provide the port number" << std::endl;
		//return 1;
	}
	
	con = new Connection(); 
	int connectionDescriptor = con->openPort(atoi(argv[1]), 9600);

	wsQueue = new PacketQueue();
	zbReceiveQueue = new PacketQueue();
	localZBReceiveQueue = new std::queue<Packet *>;
	localWSQueue = new std::queue<Packet *>;

	mainConditionVariable = new std::condition_variable;
	conditionVariableMutex = new std::mutex;

	zbSenderQueue = new PacketQueue();
	zbSenderConditionVariableMutex = new std::mutex;
	zbSenderConditionVariable = new std::condition_variable;

	zbSender = new ZBSender(connectionDescriptor, zbSenderConditionVariableMutex, zbSenderConditionVariable, zbSenderQueue);
	zbSenderThread = new boost::thread(boost::ref(*zbSender));

	zbReceiver = new ZBReceiver(connectionDescriptor, conditionVariableMutex, mainConditionVariable, zbReceiveQueue);
	zbReceiverThread = new boost::thread(boost::ref(*zbReceiver));

	webService = new Webservice (wsQueue, mainConditionVariable, conditionVariableMutex);

	ipsumSendQueue = new PacketQueue();
	ipsumReceiveQueue = new PacketQueue();
	ipsumConditionVariable = new std::condition_variable;
	ipsumConditionVariableMutex = new std::mutex;
	localIpsumSendQueue = new std::queue<Packet *>;
	localIpsumReceiveQueue = new std::queue<Packet *>;

	ipsum = new Ipsum(ipsumSendQueue, ipsumReceiveQueue, conditionVariableMutex, mainConditionVariable, ipsumConditionVariableMutex, ipsumConditionVariable);

	packetsWaitingForResponse = new std::queue<std::pair<Packet*, time_t>>;
}

MainClass::~MainClass()
{
	delete socket;
	delete con;
	
	delete mainConditionVariable;
	delete conditionVariableMutex;

	delete zbSenderQueue;
	delete zbSenderConditionVariableMutex;
	delete zbSenderConditionVariable;
	delete zbSender;
	delete zbSenderThread;

	delete zbReceiveQueue;
	delete localZBReceiveQueue;
	delete zbReceiver;


	
	delete wsQueue;
	delete localWSQueue;
	delete webService;

	delete ipsumSendQueue;
	delete ipsumReceiveQueue;
	delete ipsumConditionVariable;
	delete ipsumConditionVariableMutex;
	delete localIpsumSendQueue;
	delete localIpsumReceiveQueue;
	delete ipsum;
//	delete wsThread;
	delete packetsWaitingForResponse; 
}

void MainClass::operator() ()
{

	std::cout << "going into main while loop" << std::endl;
	while(true)
	{
		{	// Scope of unique_lock
			std::unique_lock<std::mutex> uniqueLock(*conditionVariableMutex);
			mainConditionVariable->wait(uniqueLock, [this]{ return ((!zbReceiveQueue->empty()) || (!wsQueue->empty() || (!ipsumReceiveQueue->empty()))); });
			std::cout << "mainconditionvariable notification received" << std::endl;
			while(!zbReceiveQueue->empty())

			{
				localZBReceiveQueue->push(zbReceiveQueue->getPacket());
			}
			
			while(!wsQueue->empty())
			{
				localWSQueue->push(wsQueue->getPacket());
			}
			
			while(!ipsumReceiveQueue->empty())
			{
				localIpsumReceiveQueue->push(ipsumReceiveQueue->getPacket());
			}
		}
		// Shared queue is no longer locked, now ready to process the packets
		Packet * packet;
		while(!localZBReceiveQueue->empty())
		{
			packet = localZBReceiveQueue->front();
			localZBReceiveQueue->pop();
			if(typeid(packet) ==  typeid(LibelIOPacket *))
			{
				std::cout << "ZB_LIBEL_IO received in main" << std::endl;
				libelIOHandler(packet);
			}
						
		}
		
		while(!localWSQueue->empty())
		{
			packet = localWSQueue->front();
			localWSQueue->pop();
			if(typeid(packet) ==  typeid(WSPacket *))
			{
				std::cout << "WS_PACKET received in main" << std::endl;
				webserviceHandler(packet*);	
			}
		}

		while(!localIpsumReceiveQueue->empty())
		{
			packet = localIpsumReceiveQueue->front();
			localIpsumReceiveQueue->pop();
			/*
			if(typeid(packet) ==  typeid(IpsumPacket *))
			{
				std::cout << "Ipsum_PACKET received in main" << std::endl;
				
				std::cout << "post data: "  << (dynamic_cast<WSPacket *> (packet))->getRequestData() << std::endl;
			}
			*/
		}


	}
	zbReceiverThread->join();
}

void MainClass::libelIOHandler(Packet * packet)
{
	LibelIOPacket * libelIOPacket = dynamic_cast<LibelIOPacket *> (packet);
	std::cout << "temperature: " << libelIOPacket->getTemperature() << std::endl;
}

void MainClass::webserviceHandler(Packet * packet)
{
	WSPacket * wsPacket = dynamic_cast<WSPacket *> (packet);
	switch(wsPacket->getRequestType())
	{
		case CHANGE_FREQUENCY:
			changeFrequencyRequest(wsPacket);
			break;
		case ADD_NODE:
			break;
		case ADD_SENSOR:
		     	break;
		case REQUEST_DATA:
			requestIOHandler(wsPacket);
		     	break;
		default:
		     std::cerr << "unrecognized packet" << std::endl;

	}
}

void MainClass::changeFrequencyHandler(Packet * packet)
{
	

}

void MainClass::addNodeHandler(Packet * packet)
{
	

}

void MainClass::addSensorHandler(Packet * packet)
{

}

void MainClass::requestIOHandler(Packet * packet)
{
	

}
