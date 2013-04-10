
CC = g++
LFLAGS = -Wall -Werror -std=c++11 -g -lxerces-c -lboost_thread -lboost_date_time -DDEBUG
CFlAGS = -Wall -Werror -std=c++11 -g -DDEBUG
#SOURCES = ZBReceiver.cpp
#DEPENDENCIES = $(SOURCES:.cpp=.h)
#OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS = ZBReceiver.o ZBSender.o ./packets/receivepacket.o ./packets/dataIOPacket.o connection.o\
	 ./packets/transmitrequestpacket.o ./packets/ZBPacket.o ./packets/outgoingpacket.o\
       	 ./packets/incomingpacket.o ./packets/libelchangenodefreqpacket.o ./packets/libelchangefreqpacket.o ./packets/libeliopacket.o\
	 ./packets/libeladdnodepacket.o ./packets/libeladdnoderesponse.o ./packets/libelrequestiopacket.o ./packets/libelmaskrequest.o\
	 ./packets/libelmaskresponse.o

RM = /bin/rm -f

all : $(OBJECTS)

packet_test.out :
	$(CC) $(LFLAGS) packet_test.cpp -o ./tests/packet_test.out ./packets/ZBPacket.o ../packet.o ./packets/outgoingpacket.o ./packets/libelchangefreqpacket.o ./packets/transmitrequestpacket.o ./packets/libeliopacket.o ./packets/receivepacket.o ./packets/incomingpacket.o ./packets/libeladdnoderesponse.o ./packets/libeladdnodepacket.o ./packets/libelrequestiopacket.o ../testclass.h

$(OBJECTS): %.o:  %.cpp %.h
	$(CC) -c $(CFlAGS) $< -o $@


clean:
	$(RM) $(OBJECTS)
