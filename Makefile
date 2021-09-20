.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=serv_6  cln_6
all:$(BIN)
%.O:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.0 $(BIN)

