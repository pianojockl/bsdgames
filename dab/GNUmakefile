CC = g++
CCFLAGS = -Wall -g
INCLUDEDIR = ./
LDFLAGS = -lncurses -lm
OUTPUT = dab
SOURCES = algor.cc board.cc main.cc human.cc box.cc player.cc gamescreen.cc ttyscrn.cc random.cc
OBJECTS=$(SOURCES:.c=.o)

all : $(OUTPUT)

clean:
	rm -f $(OUTPUT) *.o *~

$(OUTPUT): $(OBJECTS)
	    $(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	    $(CC) -I$(INCLUDEDIR) -c $(CCFLAGS) $<



