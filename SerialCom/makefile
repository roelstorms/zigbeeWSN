
CC = g++
CFlAGS = -Wall -Werror -std=c++11 -g
#SOURCES = ZBReceiver.cpp
#DEPENDENCIES = $(SOURCES:.cpp=.h)
#OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS = ZBReceiver.o ZBSender.o ./packets/libeliopacket.o ./packets/receivepacket.o ./packets/dataIOPacket.o connection.o\
	./packets/libeladdnodepacket.o ./packets/transmitrequestpacket.o 
RM = /bin/rm -f

all : $(OBJECTS)

$(OBJECTS): %.o:  %.cpp %.h
	$(CC) -c $(CFlAGS) $< -o $@


clean:
	$(RM) $(OBJECTS)
