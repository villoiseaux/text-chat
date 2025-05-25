CC=cc
CFLAGS=-I.
DEPS=server.h
OBJ=server.o textchat.o
BINARY=textchat

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINARY): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o core $(BINARY)