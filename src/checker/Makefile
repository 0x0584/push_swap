#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/03 22:53:41 by archid-           #+#    #+#              #
#    Updated: 2019/10/11 18:29:37 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# this is the checker's Makefile

# NOTE: Makefiles do not work as expected! compiling manually now!

# why create a static library?
# just create a core object and
# compile it with everything else

DEBUG	:= 1
NAME	= checker

FTDIR	= ../libft
LDFT	= -L$(FTDIR) -lft

SRC		:= $(wildcard *.c)

LDFLAGS	= -L../../core -lcore
DEPS	= -I../include -I$(FTDIR)
CFLAGS 	= -Wall -Wextra
CC		= gcc $(CFLAGS)

ifeq ($(DEBUG), 1)
	CFLAGS += -ggdb
else
	CFLAGS += -Werror
endif

all:
	$(CC) $(SRC) -o $(NAME) $(DEPS) $(LDFT) $(LDFLAGS)
