CC=cc
CFLAGS=-I.
DEPS=server.h logs.h
OBJ=server.o textchat.o logs.o
BINARY=textchat

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINARY): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o core $(BINARY)