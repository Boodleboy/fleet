CC = gcc
CFLAGS = -Wall -Wextra -g 

TARGET = server
TESTTARG = testsuite

SRCDIR = src
OBJDIR = obj
TSTDIR = test
TSTOBJDIR = test/obj

FILES = client\
	server\
	middleman\
	cons\
	hashmap

TFILES = main

HFILES = fns.h\
	dat.h\
	hashmap.h

SRC = $(FILES:%=$(SRCDIR)/%.c)
OBJ = $(FILES:%=$(OBJDIR)/%.o)
HDR = $(HFILES:%=$(SRCDIR)/%)

TSTSRC = $(TFILES:%=$(TSTDIR)/%.c)
TSTOBJ = $(TFILES:%=$(TSTOBJDIR)/%.o)
TSTDEP = $(filter-out $(OBJDIR)/server.o,$(OBJ))

.PHONY: test

$(TARGET): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^ -lixp 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TSTOBJDIR)/%.o: $(TSTDIR)/%.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

testsuite: $(TSTOBJ) $(TSTDEP)
	echo $(TSTDEP)
	$(CC) $(CFLAGS) -o $@ $^ -lixp -lcheck

test: testsuite
	./testsuite

clean:
	rm -f $(OBJ) $(TARGET) $(TSTOBJ) $(TESTTARG)

run:
	./$(TARGET)
