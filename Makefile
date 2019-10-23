all:
	gcc -Wall -Wextra -ggdb src/*.c -ochecker -Iinclude -Ilibft -Llibft -lft
