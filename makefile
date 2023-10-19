CC = gcc
CFLAGS = -Wall -Wextra -g -lixp -lapr-1 -laprutil-1

TARGET = fleet
TESTTARG = testsuite

SRCDIR = src
OBJDIR = src/obj
TSTDIR = test
TSTOBJDIR = test/obj

FILES = main\
		error

TFILES = main\
		 dummy\
		 error

HFILES = ixp.h\
		 error.h

THFILES = suites.h

SRC = $(FILES:%=$(SRCDIR)/%.c)
OBJ = $(FILES:%=$(OBJDIR)/%.o)
HDR = $(HFILES:%=$(SRCDIR)/%)
THDR = $(THFILES:%=$(TSTDIR)/%)

TSTSRC = $(TFILES:%=$(TSTDIR)/%.c)
TSTOBJ = $(TFILES:%=$(TSTOBJDIR)/%.o)
TSTDEP = $(filter-out $(OBJDIR)/main.o,$(OBJ))

.PHONY: test

$(TARGET): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^ 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TSTOBJDIR)/%.o: $(TSTDIR)/%.c $(HDR) $(THDR)
	$(CC) $(CFLAGS) -c $< -o $@

testsuite: $(TSTOBJ) $(TSTDEP)
	echo $(TSTDEP)
	$(CC) $(CFLAGS) -o $@ $^ -lcheck

test: testsuite
	./testsuite

clean:
	rm -f $(OBJ) $(TARGET) $(TSTOBJ) $(TESTTARG)

run:
	./$(TARGET)
