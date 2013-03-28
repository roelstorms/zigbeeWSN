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

	
	try
	{
		socket->ipsumInfo();
	}
	catch(HttpError)
	{
		std::cerr << "Could not connect to Ipsum" << std::endl;
		//return 1;
	}

	
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
			switch(packet->getType())
			{
				case ZB_LIBEL_IO:
				std::cout << "ZB_LIBEL_IO received in main" << std::endl;
				
				std::cout << "temperature: "  << (dynamic_cast<LibelIOPacket *> (packet))->getTemperature() << std::endl;
				break;
				case ZB_LIBEL_CHANGEFREQ_REPLY:

				std::cout << "ZB_LIBEL_CHANGEFREQ_REPLY received in main" << std::endl;
				break;
				case ZB_LIBEL_ADDNODE_REPLY:

				std::cout << "ZB_LIBEL_ADDNODE_REPLY received in main" << std::endl;
				break;
				default:	//unknown type

				std::cerr << "zbSendQueue had a packet with an incorrect type" << std::endl;
			}
		}
		
		while(!localWSQueue->empty())
		{
			packet = localWSQueue->front();
			localWSQueue->pop();
			switch(packet->getType())
			{
				case WS_COMMAND:

				std::cout << "WS_COMMAND received in main" << std::endl;
				break;
				default:	//unknown type

				std::cerr << "wsQueue had a packet with an incorrect type" << std::endl;
			}
		}

		while(!localIpsumReceiveQueue->empty())
		{
			packet = localIpsumReceiveQueue->front();
			localIpsumReceiveQueue->pop();
			switch(packet->getType())
			{
				case WS_COMMAND:

				std::cout << "WS_COMMAND received in main" << std::endl;
				break;
				default:	//unknown type

				std::cerr << "wsQueue had a packet with an incorrect type" << std::endl;
			}
		}


	}
	zbReceiverThread->join();
	wsThread->join();
}

void libelIOHandler(Packet * packet)
{
	LibelIOPacket * libelIOPacket = dynamic_cast<LibelIOPacket *> (packet);
	std::cout << "temperature: " << libelIOPacket->getTemperature() << std::endl;
}
