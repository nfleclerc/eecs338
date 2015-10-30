NAME := as5
SOURCE := $(wildcard *.c)
OUTPUT := main.o
CC := gcc
ARGS := -Wall -g -Werror
LIBS := -pthread

.PHONY: clean distclean

all: $(SOURCE)
	$(CC) $(ARGS) $(SOURCE) -o $(OUTPUT) $(LIBS)

clean:
	@- $(RM) $(OUTPUT)

distclean: clean
