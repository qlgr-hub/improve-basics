
CC := /usr/bin/gcc
AR := /usr/bin/ar
CFLAG := -Wall -D_UNP_DEMO_

SRCS := $(wildcard ./*.c)
OBJS := $(SRCS:./%.c=./%.o)

OUTPUTLIB_D := ../lib/debug/libunpcom.a
OUTPUTLIB_R := ../lib/release/libunpcom.a

all: debug release

debug:
	rm -rf $(OUTPUTLIB_D)
	$(CC) -c -g $(CFLAG) $(SRCS)
	$(AR) -rv $(OUTPUTLIB_D) $(OBJS)

release:
	rm -rf $(OUTPUTLIB_R)
	$(CC) -c -O2 $(CFLAG) $(SRCS)
	$(AR) -rv $(OUTPUTLIB_R) $(OBJS)

.PHONY: all clean

clean:
	rm -rf $(OUTPUTLIB_D)
	rm -rf $(OUTPUTLIB_R)