# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybarbier <ybarbier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/01 14:16:31 by ybarbier          #+#    #+#              #
#    Updated: 2017/05/01 16:43:52 by ybarbier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#_____________CONFIG____________#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

PATH_SRC = ./src/

PATH_INC = ./inc

PATH_INC_LIBFT = ./libft/includes/

INCLUDES = -I $(PATH_INC) -I $(PATH_INC_LIBFT)

CC = cc
#CFLAGS = -Wall -Wextra -Werror -Ofast $(INCLUDES)
CFLAGS = $(INCLUDES)
LIBS = -L libft/ -lft

#_____________FILES____________#

SRC =	main.c \
	malloc.c \
	realloc.c \
	free.c \
	block_initialisation.c \
	block_creation.c \
	zone_initialisation.c \
	zone_creation.c \
	zone_deletion.c \
	ft_puthexa.c \
	show_alloc_mem.c


OBJ = $(addprefix $(PATH_SRC), $(SRC:.c=.o))

#____________RULES_____________#

.PHONY: clean fclean re test

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(OBJ) -o $(NAME) $(LIBS)

#____CLEAN____#

clean:
	rm -f $(OBJ)

#___FCLEAN___#

fclean: clean
	rm -f $(NAME)

#____RE____#

re: fclean all
