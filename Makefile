#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njacobso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/19 16:28:47 by njacobso          #+#    #+#              #
#    Updated: 2019/07/28 20:09:22 by ydavis           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= game
CFLAGS		= -o3 #-Wall -Werror -Wextra
FILES		= *.c
INCLUDES	= include
LIBFT		= 
LIBSDL		=
ifeq ($(shell uname), Linux)
	LIBSDL	+= -lSDL2 -lSDL2main -lm
	LIBFT	+= lib/libft/*.c
else
	LIBSDL	+= -L lib/sdl -lSDL2
	LIBFT	+= -L lib/libft -lft
endif

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) -I $(INCLUDES) $(LIBSDL) $(LIBFT) $(FILES) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
