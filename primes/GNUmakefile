CC = gcc
CCFLAGS = -Wall -g
INCLUDEDIR = ./
LDFLAGS = -lm
OUTPUT = primes
SOURCES = primes.c pr_tbl.c pattern.c
OBJECTS=$(SOURCES:.c=.o)

all : $(OUTPUT)

clean:
	rm -f $(OUTPUT) *.o *~

$(OUTPUT): $(OBJECTS)
	    $(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	    $(CC) -I$(INCLUDEDIR) -c $(CCFLAGS) $<



