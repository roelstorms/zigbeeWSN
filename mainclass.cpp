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
	zbSendQueue = new PacketQueue();
	localZBSendQueue = new std::queue<Packet *>;
	mainConditionVariable = new std::condition_variable;
	conditionVariableMutex = new std::mutex;


	ZBReceiver zbReceiver(connectionDescriptor, conditionVariableMutex, mainConditionVariable, zbSendQueue);
	zbReceiverThread = new boost::thread(boost::ref(zbReceiver));

	Webservice webService (wsQueue, mainConditionVariable, conditionVariableMutex);

}

MainClass::~MainClass()
{
	delete socket;
	delete con;
	delete zbSendQueue;
	delete localZBSendQueue;
	delete mainConditionVariable;
	delete conditionVariableMutex;
	delete wsQueue;
}

void MainClass::operator() ()
{

	std::cout << "going into main while loop" << std::endl;
	while(true)
	{
		{	// Scope of unique_lock
			std::unique_lock<std::mutex> uniqueLock(*conditionVariableMutex);
			mainConditionVariable->wait(uniqueLock, [this]{ return (!zbSendQueue->empty()); });
			while(!zbSendQueue->empty())
			{
				localZBSendQueue->push(zbSendQueue->getPacket());	
			}
		}
		// Shared queue is no longer locked, now ready to process the packets
		Packet * zbPacket;
		while(!localZBSendQueue->empty())
		{
			zbPacket = localZBSendQueue->front();
			localZBSendQueue->pop();
			switch(zbPacket->getType())
			{
				case ZB_LIBEL_IO:
				std::cout << "ZB_LIBEL_IO received in main" << std::endl;
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
	}
	zbReceiverThread->join();
}

void libelIOHandler(Packet * packet)
{
	LibelIOPacket * libelIOPacket = dynamic_cast<LibelIOPacket *> (packet);
	std::cout << "temperature: " << libelIOPacket->getTemperature() << std::endl;
}
