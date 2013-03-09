
all:	datahandler.o	
	g++ dataToIpsum.cpp -o dataToIpsum.out DataHandler.o ./SerialCom/obj/connection.o ./SerialCom/obj/inputhandler.o ./HTTP/http.o ./XML/XML.o -lcurl -lxerces-c -lboost_thread -lboost_date_time -std=c++11
datahandler.o :
	g++ -c DataHandler.cpp -o DataHandler.o -std=c++11
clean:
	rm dataToIpsum.out
