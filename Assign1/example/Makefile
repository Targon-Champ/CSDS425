
CC=gcc
CXX=g++
LD=gcc
CFLAGS=-Wall -Werror -g
LDFLAGS=$(CFLAGS)

TARGETS=proj1

all: $(TARGETS)

sample: sample.o
	$(CC) $(CFLAGS) -o $@ $< 

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.cc
	$(CXX) $(CFLAGS) -c $<

clean:
	rm -f *.o

distclean: clean
	rm -f $(TARGETS)
