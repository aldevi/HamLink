all: config_parser.o

config_parser.o: config_parser.c config_parser.h
	$(CC) $(CFLAGS) -c config_parser.c

clean:
	rm -f *.o *.e *.pi *.tar.gz

.PHONY: all clean