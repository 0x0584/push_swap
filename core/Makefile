#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/03 22:54:21 by archid-           #+#    #+#              #
#    Updated: 2019/10/11 18:21:58 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

DEBUG	:= 1
NAME	= libcore.a

FTDIR	= ../libft
LDFT	= -L$(FTDIR) -lft -I$(FTDIR)

OBJS	:= $(patsubt %.c, %.o, $(wildcard *.c))

LDFLAGS	= -I../include
CFLAGS 	= -Wall -Wextra -c
CC		= gcc $(CFLAGS)


ifeq ($(DEBUG), 1)
	CFLAGS += -ggdb
else
	CFLAGS += -Werror
endif

all: $(OBJS)
	make $(FTDIR)
	@rm $(NAME)
	@ar rc $(NAME) $(shell find $(FTDIR) -name '*.o') $^

%.o: %.c
	$(CC) $< -o $@ $(LDFLAGS) $(LDFT)
# IDEA: About Makefiles, the repo should have 3 repos, game, push_swap, checker.
# each one has its own makefile, and the main makefile create two symbolic links
# at the root of the repo: push_swap and checker.
