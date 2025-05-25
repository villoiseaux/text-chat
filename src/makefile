CC=cc
CFLAGS=-I.
DEPS=server.h
OBJ=server.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

textchat: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
