CC = gcc
CCFLAGS = -Wall -g
INCLUDEDIR = ./
LDFLAGS =
OUTPUT = adventure
SOURCES = main.c init.c done.c save.c subr.c vocab.c wizard.c io.c data.c crc.c
CLEANFILES=data.c setup
OBJECTS=$(SOURCES:.c=.o)

all : $(OUTPUT)

data.c: glorkz setup
	./setup glorkz > data.c

clean:
	rm -f $(OUTPUT) $(CLEANFILES) *.o *~

$(OUTPUT): $(OBJECTS)
	    $(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	    $(CC) -I$(INCLUDEDIR) -c $(CCFLAGS) $<



