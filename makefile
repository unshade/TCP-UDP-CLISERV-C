CC = clang
CFLAGS = -Wall -Werror -g
SERVER = serveurTCP
CLIENT = clientTCP

all: $(SERVER) $(CLIENT)

$(SERVER): $(SERVER).c
	$(CC) $(CFLAGS) -o $(SERVER) $(SERVER).c

$(CLIENT): $(CLIENT).c
	$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT).c

clean:
	rm -f $(SERVER) $(CLIENT)
