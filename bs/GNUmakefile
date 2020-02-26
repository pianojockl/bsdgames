LDFLAGS = -lm -lncurses
OUTPUT = bs

all: bs

caesar: bs.c
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(OUTPUT) *.o *~
