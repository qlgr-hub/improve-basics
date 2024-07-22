
CC := /usr/bin/gcc
CFLAG := -Wall

SRCS := ./checksockopt.c
OBJS := ./checksockopt.o

OUTPUT_D := ../output/debug/checksockopt
OUTPUT_R := ../output/release/checksockopt

LIB_D := ../lib/debug/
LIB_R := ../lib/release/

all: debug release

debug:
	rm -rf $(OUTPUT_D)
	$(CC) -c -g $(CFLAG) $(SRCS)
	$(CC) $(OBJS) -L$(LIB_D) -lunpcom -o $(OUTPUT_D)

release:
	rm -rf $(OUTPUT_R)
	$(CC) -c -O2 $(CFLAG) $(SRCS)
	$(CC) $(OBJS) -L$(LIB_R) -lunpcom -o $(OUTPUT_R)

.PHONY: all clean

clean:
	rm -rf $(OUTPUT_D)
	rm -rf $(OUTPUT_R)