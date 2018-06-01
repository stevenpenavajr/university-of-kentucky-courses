GOAL = mycloudclient
CFLAGS = -Wall -g -O0 -fno-stack-protector
all: $(GOAL)
asm: $(GOAL)
	objdump -d $(GOAL) > $(GOAL).s
clean:
	rm -f $(GOAL) $(GOAL).s


CFLAGS = -Wall -g
CPPFLAGS = -Wall -std=c++11 -g

CLIENTS = mycloudclient

all: $(CLIENTS)

csapp.h:
	wget http://csapp.cs.cmu.edu/2e/ics2/code/include/csapp.h

csapp.c:
	wget http://csapp.cs.cmu.edu/2e/ics2/code/src/csapp.c

csapp.o: csapp.h csapp.c
	gcc -c csapp.h csapp.c


mycloudclient: mycloudclient.cpp csapp.o
	g++ $(CPPFLAGS) mycloudclient.cpp csapp.o -lpthread -o mycloudclient

.PHONY: clean
clean:
	/bin/rm -rf csapp.h csapp.c *.o mycloudclient
