#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/01 23:13:45 by archid-           #+#    #+#              #
#    Updated: 2019/11/15 20:38:34 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ARGS		= 1 5 4 2 7 3 8
CORE_SRCS 	= src/op.c src/ps.c src/reader.c src/helper.c

PUSH_SWAP	= src/push_swap.c
CHECKER 	= src/checker.c 

.PHONY: all it

all:
	make -C libft
	gcc -g $(CORE_SRCS) $(PS_SRCS) -o push_swap -Iinclude -Ilibft -lft -Llibft
	gcc -g $(CORE_SRCS) $(CHK_SRCS) -o checker -Iinclude -Ilibft -lft -Llibft

it: all
	./checker $(ARGS) < ./push_swap $(ARGS)
