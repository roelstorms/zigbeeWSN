# this is a example of Makefile

all:	DataIOPacket.o inputhandler.o connection.o userinput.o APIFrames.o  ATCommandResponsePacket.o sendpacket.o datapacket.o
	g++ main.cpp -o main.out ./obj/inputhandler.o ./obj/SendPacket.o ./obj/connection.o ./obj/userinput.o ./obj/APIFrames.o ./obj/dataIOPacket.o ./obj/datapacket.o ./obj/ATCommandPacket.o ./obj/packet.o ../HTTP/http.o ../XML/XML.o -lxerces-c -lboost_date_time -lboost_thread -std=c++11 -lcurl -g

ZBReceiver.o:
	g++ -c ZBReceiver.cpp -o ./obj/ZBReceiver.o -std=c++11 -g
ZBSender.o:
	g++ -c ZBSender.cpp -o ./obj/ZBSender.o -std=c++11 -g
connection.o: 
	g++ -c connection.cpp -o ./obj/connection.o -lboost_thread -std=c++11 -g

	
ZBPacket.o:
	g++ -c ZBPacket.cpp -o ./obj/ZBPacket.o -std=c++11 -g
DataIOPacket.o: 
	g++ -c dataIOPacket.cpp -o ./obj/dataIOPacket.o -std=c++11 -g
datapacket.o: 
	g++ -c datapacket.cpp -o ./obj/datapacket.o -std=c++11 -g
libeliopacket.o: 
	g++ -c libeliopacket.cpp -o ./obj/libeliopacket.o -std=c++11 -g
clean:
	rm ./obj/inputhandler.o ./obj/connection.o ./obj/userinput.o ./obj/APIFrames.o -g
