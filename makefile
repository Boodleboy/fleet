CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = client

SRC = client.c\
		 middleman.c\
		 cons.c\
		 hashmap.c

HEADERS = fns.h\
		 dat.h\
		 hashmap.h

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run:
	./client
