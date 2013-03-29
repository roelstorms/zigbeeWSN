# this is a example of Makefile

ZBReceiver.o:
	g++ -c ZBReceiver.cpp -o ./obj/ZBReceiver.o -std=c++11 -g
ZBSender.o:
	g++ -c ZBSender.cpp -o ./obj/ZBSender.o -std=c++11 -g
connection.o: 
	g++ -c connection.cpp -o ./obj/connection.o -lboost_thread -std=c++11 -g

	
ZBPacket.o:
	g++ -c ./packets/ZBPacket.cpp -o ./packets/obj/ZBPacket.o -std=c++11 -g
DataIOPacket.o: 
	g++ -c ./packets/dataIOPacket.cpp -o ./packets/obj/dataIOPacket.o -std=c++11 -g
datapacket.o: 
	g++ -c ./packets/datapacket.cpp -o ./packets/obj/datapacket.o -std=c++11 -g
libeliopacket.o: 
	g++ -c ./packets/libeliopacket.cpp -o ./packets/obj/libeliopacket.o -std=c++11 -g
libeladdnodepacket.o: 
	g++ -c ./packets/libeladdnodepacket.cpp -o ./packets/obj/libeladdnodepacket.o -std=c++11 -g
clean:
	rm ./obj/inputhandler.o ./obj/connection.o ./obj/userinput.o ./obj/APIFrames.o -g
