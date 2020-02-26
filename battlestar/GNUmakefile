CC = gcc
CCFLAGS = -Wall -g -fPIC
INCLUDEDIR = ./
LDFLAGS = -lncurses -lbsd
OUTPUT = battlestar
SOURCES = battlestar.c command1.c command2.c command3.c command4.c \
        command5.c command6.c command7.c \
        init.c cypher.c getcom.c parse.c room.c save.c fly.c misc.c \
        globals.c dayfile.c nightfile.c dayobjs.c nightobjs.c words.c

OBJECTS=$(SOURCES:.c=.o)
CLEANFILES=$(OBJECTS)

all : $(OUTPUT)

clean:
	rm -f $(OUTPUT) $(CLEANFILES) *.o *~

#$(OUTPUT): $(OBJECTS)
#	    $(CC) $(LDFLAGS) $^ $(OUTPUT).c -o $@

$(OUTPUT):
	$(CC) $(LDFLAGS) $^ $(SOURCES) -o $@

%.o: %.c
	    $(CC) -I$(INCLUDEDIR) -c $(CCFLAGS) $<



