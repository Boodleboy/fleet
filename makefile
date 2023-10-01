CC = gcc
CFLAGS = -Wall -Wextra -g 

TARGET = server
TESTTARG = testsuite

SRCDIR = src
OBJDIR = obj
TSTDIR = test
TSTOBJDIR = test/obj

FILES = server\
	middleman\
	cons\
	hashmap\
	service\
	dummysvc

TFILES = main\
		 dummy\
		 service

HFILES = fns.h\
	dat.h\
	hashmap.h

THFILES = suites.h

SRC = $(FILES:%=$(SRCDIR)/%.c)
OBJ = $(FILES:%=$(OBJDIR)/%.o)
HDR = $(HFILES:%=$(SRCDIR)/%)
THDR = $(THFILES:%=$(TSTDIR)/%)

TSTSRC = $(TFILES:%=$(TSTDIR)/%.c)
TSTOBJ = $(TFILES:%=$(TSTOBJDIR)/%.o)
TSTDEP = $(filter-out $(OBJDIR)/server.o,$(OBJ))

.PHONY: test

$(TARGET): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^ -lixp 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TSTOBJDIR)/%.o: $(TSTDIR)/%.c $(HDR) $(THDR)
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
