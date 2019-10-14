all:
	gcc -Wall -Wextra -ggdb src/checker/*.c core/*.c -o foo -Llibft -lft -Iinclude -Ilibft

