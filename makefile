CC = gcc
CFLAGS = -Wall -Wextra -g 

TARGET = main

SRC = client.c\
		 middleman.c\
		 cons.c\
		 hashmap.c

HEADERS = fns.h\
		 dat.h\
		 hashmap.h

OBJ = $(SRC:.c=.o)

# TODO: figure out organization of these files. This is a mess
test/cons: test/cons.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ cons.o client.o $^ -lixp

$(TARGET): $(OBJ) main.o 
	$(CC) $(CFLAGS) -o $@ $^ -lixp 

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

test/%.0: test/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run:
	./client
