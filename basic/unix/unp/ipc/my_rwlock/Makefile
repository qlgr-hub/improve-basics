
CC := /usr/bin/gcc
CFLAG := -Wall -D_UNP_DEMO_

SRCS := ./testcancel.c ./my_rwlock.c
OBJS := ./testcancel.o ./my_rwlock.o

OUTPUT_D := ../../output/debug/testcancel
OUTPUT_R := ../../output/release/testcancel

LIB_D := ../../lib/debug/
LIB_R := ../../lib/release/

all: debug release

debug:
	rm -rf $(OUTPUT_D)
	$(CC) -c -g $(CFLAG) $(SRCS)
	$(CC) $(OBJS) -L$(LIB_D) -lunpcom -o $(OUTPUT_D) -lsctp -lrt -lpthread

release:
	rm -rf $(OUTPUT_R)
	$(CC) -c -O2 $(CFLAG) $(SRCS)
	$(CC) $(OBJS) -L$(LIB_R) -lunpcom -o $(OUTPUT_R) -lsctp -lrt -lpthread

.PHONY: all clean

clean:
	rm -rf $(OUTPUT_D)
	rm -rf $(OUTPUT_R)