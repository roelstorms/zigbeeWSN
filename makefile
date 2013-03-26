
all:	mainclass.o test packet.o packetqueue.o	
	g++ main.cpp -o main.out ./obj/mainclass.o ./SerialCom/obj/ZBPacket.o ./SerialCom/obj/ZBReceiver.o ./SerialCom/obj/connection.o ./SerialCom/obj/libeliumIOpacket.o ./SerialCom/obj/datapacket.o ./packetqueue.o packet.o ./HTTP/http.o ./XML/XML.o -lcurl -lxerces-c -lboost_thread -lboost_date_time -std=c++11

mainclass.o:
	g++ -c mainclass.cpp -o ./obj/mainclass.o -std=c++11
test:	
	g++ mainTest.cpp -o mainTest.out -std=c++11 packet.o
packet.o:
	g++ -c packet.cpp -o packet.o -std=c++11
packetqueue.o:
	g++ -c packetqueue.cpp -o packetqueue.o -std=c++11
clean:
	rm packet.o
