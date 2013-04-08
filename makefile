
all:	mainclass.o test packet.o packetqueue.o	
	g++ main.cpp -o main.out ./obj/mainclass.o ./SerialCom/packets/ZBPacket.o ./SerialCom/ZBReceiver.o ./SerialCom/ZBSender.o ./SerialCom/connection.o ./SerialCom/packets/libeliopacket.o ./SerialCom/packets/receivepacket.o ./packetqueue.o packet.o ./SerialCom/packets/incomingpacket.o ./HTTP/http.o ./XML/XML.o ./webservice/webservice.cpp ./webservice/mongoose.o  ./webservice/wspacket.o ./HTTP/ipsum.o ./HTTP/ipsumpacket.o ./HTTP/ipsumuploadpacket.o ./sqlite/sql.o -lpthread -ldl -lcurl -lxerces-c -lboost_thread -lboost_date_time -std=c++11

mainclass.o:
	g++ -c mainclass.cpp -o ./obj/mainclass.o -std=c++11
test:	
	g++ mainTest.cpp -o mainTest.out -std=c++11 packet.o
packet.o: packet.cpp packet.h
	g++ -c packet.cpp -o packet.o -std=c++11
packetqueue.o: 
	g++ -c packetqueue.cpp -o packetqueue.o -std=c++11
clean:
	rm packet.o packetqueue.o mainTest.out
