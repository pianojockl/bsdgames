LDFLAGS = -lm
OUTPUT = caesar

all: caesar

caesar: caesar.c
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(OUTPUT) *.o *~
