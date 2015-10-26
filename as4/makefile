NAME := As4
C_SRCS := $(wildcard *.c)
OBJS := ${C_SRCS:.c=.o}
CC := gcc

.PHONY: clean distclean

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -Wall $(C_SRCS) -o $(OBJS) -lm

clean:
	@- $(RM) $(OBJS)

distclean: clean
