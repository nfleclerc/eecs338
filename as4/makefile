NAME := as4
C_SRCS := $(wildcard *.c)
OBJS := ${program_C_SRCS:.c=.o}

.PHONY: all clean distclean

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) -o $(NAME)

clean:
	@- $(RM) $(OBJS)

distclean: clean
