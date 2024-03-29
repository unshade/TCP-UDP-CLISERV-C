CC = clang
CFLAGS = -Wall -Werror -g
SERVER = serveurTCP
CLIENT = clientTCP

UDPSERVER = serveurUDP
UDPCLIENT = clientUDP

tcp: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER).c
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER).c

$(CLIENT): $(CLIENT).c
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT).c


udp: $(UDPSERVER).a $(UDPCLIENT).a

$(UDPSERVER): $(UDPSERVER).c
	$(CC) $(CFLAGS) -o $(UDPSERVER) $(UDPSERVER).c

$(UDPCLIENT): $(UDPCLIENT).c
	$(CC) $(CFLAGS) -o $(UDPCLIENT) $(UDPCLIENT).c

all: tcp udp

clean:
	rm -f $(SERVER) $(CLIENT) $(UDPSERVER) $(UDPCLIENT)
