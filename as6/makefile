NAME := as6
SOURCE := $(wildcard *.c)
OUTPUT := main.o
RPC_STUBS := cookie.h cookie_clnt.c cookie_xdr.c cookie_svc.c
CC := gcc
ARGS := -Wall -g -Werror
LIBS := -pthread

.PHONY: clean distclean

all: $(SOURCE)
	$(CC) $(ARGS) $(SOURCE) -o $(OUTPUT) $(LIBS)

clean:
	@- $(RM) $(OUTPUT)

clean-rpc:
	@- $(RM) $(RPC_STUBS)

distclean: clean
