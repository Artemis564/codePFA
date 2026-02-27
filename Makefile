CC=gcc
CFLAGS=-Wall -Wextra -lm

all: integration pfa

integration: test_integration.o integration.o
	$(CC) -o test_integration $^ $(CFLAGS)

test_integration.o: test_integration.c integration.h
	$(CC) -c test_integration.c

integration.o: integration.c integration.h
	$(CC) -c integration.c

pfa: test_pfa.o pfa.o integration.o
	$(CC) -o test_pfa $^ -fsanitize=address,undefined -g $(CFLAGS)

test_pfa.o: test_pfa.c pfa.h
	$(CC) -c test_pfa.c

pfa.o: pfa.c pfa.h integration.h
	$(CC) -c pfa.c

clean:
	rm -f *.o test_pfa test_integration
