all:	ipsum.o	

test: http.o  http_test.cpp
	g++ http_test.cpp -o http_test.out http.o ../XML/XML.o -lcurl -lxerces-c -lboost_date_time -g -std=c++11
http.o:
	g++ -c http.cpp -o http.o -lcurl -lboost_thread -lboost_date_time -std=c++11 -g
ipsum.o: ipsumpacket.o ipsum.cpp ipsum.h
	g++ -c ipsum.cpp -o ipsum.o -std=c++11 -g
ipsumpacket.o: ipsumuploadpacket.o ipsumpacket.cpp ipsumpacket.h
	g++ -c ipsumpacket.cpp -o ipsumpacket.o -std=c++11 -g
ipsumuploadpacket.o: ipsumuploadpacket.cpp ipsumuploadpacket.h
	g++ -c ipsumuploadpacket.cpp -o ipsumuploadpacket.o -std=c++11 -g
clean:
	rm http.o ipsumpacket.o ipsum.o ipsumuploadpacket.o




