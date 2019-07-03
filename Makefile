#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njacobso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/19 16:28:47 by njacobso          #+#    #+#              #
#    Updated: 2019/05/06 20:12:55 by njacobso         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= game
CFLAGS		= -o1 -o2 -o3 #-Wall -Werror -Wextra
FILES		= *.c
#LIBSLD		= -lSDL2 -lSDL2main -lm
INCLUDES	= include
LIBSDL		= -L lib/sdl -lSDL2
LIBFT		= -L lib/libft -lft

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) -I $(INCLUDES) $(LIBSDL) $(LIBFT) $(FILES) -o $(NAME)

clean:
	rm -rf $(NAME)
	clear

fclean: clean

re: fclean all