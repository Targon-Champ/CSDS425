CC=gcc
CXX=g++
LD=g++
CFLAGS=-Wall -Werror -g -std=c++11
LDFLAGS=$(CFLAGS)

TARGETS=proj1

all: $(TARGETS)

proj1: proj1.o
	$(LD) $(LDFLAGS) -o $@ $<

proj1.o: proj1.cpp
	$(CXX) $(CFLAGS) -c $<

clean:
	rm -f *.o

distclean: clean
	rm -f $(TARGETS)
