#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/29 14:25:35 by archid-           #+#    #+#              #
#    Updated: 2019/10/29 14:55:43 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

FTDIR		= libft
SRCSDIR		= src
DEPSDIR		= include

CORE_SRC	= op.c ps.c
CHECKER_SRC	= reader.c checker.c

DEPS		= -I $(DEPSDIR) -I $(FTDIR)
LDFLAGS		= -Llibft -lft
CFLAGS		= -Wall -Werror -Wextra

CORE_OBJS	= $(patsubst %.o, %c)

info:
	echo "info: run make [all|checker|push_swap]"

all: checker push_swap
	gcc -Wall -Wextra -ggdb src/*.c -ochecker -Iinclude -Ilibft -Llibft -lft

checker:
	gcc -Wall -Wextra -ggdb -ochecker -Iinclude -Ilibft -Llibft -lft

push_swap:

core:
	gcc $(CFLAGS) -c $(CORE_SRC)
