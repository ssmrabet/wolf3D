# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smrabet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/27 15:48:45 by smrabet           #+#    #+#              #
#    Updated: 2017/01/03 12:04:05 by smrabet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

HEAD = wolf.h

LIB = libft/

SRC = src/main.c \
	  src/key.c \
	  src/menu.c \
	  src/wolf.c \

GCC = gcc -Wall -Wextra -Werror -lmlx -framework OpenGL -framework Appkit

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@$(GCC) -o $(NAME) $(OBJ) -L$(LIB) -lft
	@echo "\033[0;33;32mmake Wolf"

%.o: %.c $(HEAD)
	@$(GCC)  -c $<

clean:
	@make clean -C $(LIB)
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB)

re: fclean all
