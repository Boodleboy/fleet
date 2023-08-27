CC = gcc
CFLAGS = -Wall -Wextra -g 

TARGET = server

SRCDIR = src
OBJDIR = obj

FILES = client\
	server\
	middleman\
	cons\
	hashmap

HFILES = fns.h\
	dat.h\
	hashmap.h

SRC = $(FILES:%=$(SRCDIR)/%.c)
OBJ = $(FILES:%=$(OBJDIR)/%.o)
HDR = $(HFILES:%=$(SRCDIR)/%)

$(TARGET): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^ -lixp 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

# commenting test stuff for now
#test/%.0: test/%.c $(HDR)
#	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run:
	./$(TARGET)
