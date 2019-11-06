#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/01 23:13:45 by archid-           #+#    #+#              #
#    Updated: 2019/11/05 20:05:24 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ARGS	= 1 5 4 2 7 3 8

all:
	make -C libft re
	gcc -ggdb src/op.c src/ps.c src/push_swap.c src/reader.c src/helper.c -o push_swap -Iinclude -Ilibft -lft -Llibft
	gcc -ggdb src/op.c src/ps.c src/checker.c src/reader.c src/helper.c -o checker -Iinclude -Ilibft -lft -Llibft
