#!/bin/sh
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run.sh                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/24 23:23:09 by archid-           #+#    #+#              #
#    Updated: 2019/10/29 00:29:47 by archid-          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

make -C libft
make
./push_swap 8 5 6 3 1 2
