
NAME = bsq

SRC = ./src/*.c

INC = inc/

all:
	gcc -Wall -Wextra -Werror $(SRC) -I inc -o $(NAME)
debug:
	gcc -Wall -Wextra -Werror -DDEBUG_READ -DDEBUG -DDBG_SOLVER -DPSUM_REPR $(SRC) -I inc -o $(NAME)
clean:

fclean: clean
	rm -f $(NAME)

test:
	./tests/test.sh
