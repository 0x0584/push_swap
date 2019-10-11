#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: archid- <archid-@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/03 22:51:47 by archid-           #+#    #+#              #
#    Updated: 2019/10/11 18:02:34 by archid-          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# FIXME: try to use Gnu autotools

# FIXME: modify other Makefiles
# so that it warns if other that from this Makefilee.
# this basically would be to call a rrule directly

FTDIR		= libft
COREDIR		= core
SRCDIR		= src
CHECKER		= $(SRCDIR)/checker
PUSH_SWAP	= push_swap

RENDU		= checker push_swap

all:
	make -C $(COREDIR)
	make -C $(CHECKER)
	ln -s $(CHECKER)/checker checker

	# @make -C $(SRC_DIR)/$(PUSH_SWAP)
	# @ln -s $(SRC_DIR)/$(PUSH_SWAP)/$(PUSH_SWAP) $(PUSH_SWAP)

clean:
	@echo -e "cleaning.."
	@make -C $(COREDIR) clean
	@make -C $(SRC_DIR)/$(CHECKER) clean
	# @make -C $(SRC_DIR)/$(PUSH_SWAP) clean
	@rm -f $(RENDU)
	@echo ""

fclean:
	@echo -e "cleaning everything.."
	@make -C $(COREDIR) fclean
	@make -C $(SRC_DIR)/$(CHECKER) fclean
	# @make -C $(SRC_DIR)/$(PUSH_SWAP) fclean
	@rm -f $(RENDU)
	@echo ""

re: fclean
	@make
