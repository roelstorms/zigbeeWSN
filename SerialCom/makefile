# this is a example of Makefile

all:	DataIOPacket.o inputhandler.o connection.o userinput.o APIFrames.o  ATCommandResponsePacket.o sendpacket.o datapacket.o
	g++ main.cpp -o main.out ./obj/inputhandler.o ./obj/SendPacket.o ./obj/connection.o ./obj/userinput.o ./obj/APIFrames.o ./obj/dataIOPacket.o ./obj/datapacket.o ./obj/ATCommandPacket.o ./obj/packet.o ../HTTP/http.o ../XML/XML.o -lxerces-c -lboost_date_time -lboost_thread -std=c++11 -lcurl -g
serialunblockingtest:
	g++ serialunblockingtest.cpp -o serialunblockingtest.out ./obj/inputhandler.o ./obj/connection.o ./obj/userinput.o ./obj/APIFrames.o ./obj/packet.o ../HTTP/http.o ../XML/XML.o -lxerces-c -lboost_date_time -lboost_thread -std=c++11 -g -lcurl
APIRemoteATTest: APIFrames.o
	g++ ./tests/APIFramesTest_RemoteATCommand.cpp -o ./tests/APIFramesTest_RemoteATCommand.out ./obj/APIFrames.o ./obj/connection.o ./obj/userinput.o ./obj/inputhandler.o -lboost_thread -std=c++11
APIFramesTestATCommand:
	g++ ./tests/APIFramesTest_ATCommand.cpp -o ./tests/APIFramesTest_ATCommand.out ./obj/APIFrames.o ./obj/packet.o ./obj/connection.o  ./obj/inputhandler.o ../HTTP/http.o ../XML/XML.o -lboost_date_time -lboost_thread -std=c++11 -g -lxerces-c -lcurl

DataIOTest: DataIOPacket.o
	g++ ./tests/dataIOPacketTest.cpp -o ./tests/dataIOPacketTest.out ./obj/packet.o ./obj/dataIOPacket.o ./obj/connection.o -lboost_thread -std=c++11
APIData: APIFrames.o
	g++ ./tests/APIFramesTest_Data.cpp -o ./tests/APIFramesTest_Data.out ./obj/APIFrames.o ./obj/connection.o ./obj/userinput.o ./obj/inputhandler.o -lboost_thread -std=c++11
APIRemoteATResponseTest: APIFrames.o
	g++ ./tests/ATCommandResponseTest.cpp -o ./tests/ATCommandResponseTest.out ./obj/APIFrames.o ./obj/packet.o ./obj/ATCommandResponse.o -std=c++11
unwrap: APIFrames.o
	g++ ./tests/APIFramesTest_unwrap.cpp -o ./tests/APIFramesTest_unwrap.out ./obj/APIFrames.o ./obj/connection.o ./obj/userinput.o ./obj/inputhandler.o -lboost_thread -std=c++11
ZBReceiver.o:
	g++ -c ZBReceiver.cpp -o ./obj/ZBReceiver.o -std=c++11 -g
ZBSender.o:
	g++ -c ZBSender.cpp -o ./obj/ZBSender.o -std=c++11 -g
connection.o: inputhandler.o userinput.o
	g++ -c connection.cpp -o ./obj/connection.o -lboost_thread -std=c++11 -g

APIFrames.o: ATCommandResponsePacket.o
	g++ -c APIFrames.cpp -o ./obj/APIFrames.o -std=c++11 -g

ZBPacket.o:
	g++ -c ZBPacket.cpp -o ./obj/ZBPacket.o -std=c++11 -g


ATCommandResponsePacket.o: 
	g++ -c ATCommandResponsePacket.cpp -o ./obj/ATCommandResponsePacket.o -std=c++11 -g
ATCommandPacket.o: 
	g++ -c ATCommandPacket.cpp -o ./obj/ATCommandPacket.o -std=c++11 -g
DataIOPacket.o: 
	g++ -c dataIOPacket.cpp -o ./obj/dataIOPacket.o -std=c++11 -g
datapacket.o: 
	g++ -c datapacket.cpp -o ./obj/datapacket.o -std=c++11 -g
libeliumiopacket.o: 
	g++ -c libeliumIOpacket.cpp -o ./obj/libeliumIOpacket.o -std=c++11 -g
ATCommandTest: ATCommandPacket.o
	g++ ./tests/ATCommandTest.cpp -o ./tests/ATCommandTest.out ./obj/packet.o ./obj/ATCommandPacket.o -std=c++11 -g
packetreceivequeue:
	g++ -c ./packetreceivequeue.cpp -o ./obj/packetreceivequeue.o -std=c++11
clean:
	rm ./obj/inputhandler.o ./obj/connection.o ./obj/userinput.o ./obj/APIFrames.o -g
