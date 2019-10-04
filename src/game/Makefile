#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/03 22:54:21 by archid-           #+#    #+#              #
#    Updated: 2019/10/03 23:55:00 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

DEBUG	:= 1
PSDIR 	= ../..
FTDIR	= $(PSDIR)/libft
LDFT	= -L$(FTDIR) -lft -I$(FTDIR)

SRC		:= $(wildcard *.c)

LDFLAGS	= -I$(PSDIR)/include
CFLAGS 	= -Wall -Wextra
CC		= gcc $(CFLAGS)

ifeq ($(DEBUG), 1)
	CFLAGS += -ggdb
else
	CFLAGS += -Werror
endif

EXEC	= game

all:
	@echo "making libft"
	@make -C $(FTDIR)
	@echo ""

	$(CC) $(SRC) -o $(EXEC) $(LIBFT) $(LDFT) $(LDFLAGS)
