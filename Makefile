#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/01 23:13:45 by archid-           #+#    #+#              #
#    Updated: 2019/11/14 14:15:27 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ARGS	= 1 5 4 2 7 3 8

PS_SRCS	 = src/op.c src/ps.c src/push_swap.c src/reader.c src/helper.c src/split.c src/refill.c
CHK_SRCS = src/op.c src/ps.c src/checker.c src/reader.c src/helper.c

all:
	make -C libft re
	gcc -ggdb $(PS_SRCS) -o push_swap -Iinclude -Ilibft -lft -Llibft
	gcc -ggdb $(CHK_SRCS) -o checker -Iinclude -Ilibft -lft -Llibft
