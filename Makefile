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
LIBSLD		= -lSDL2 -lSDL2main -lm
LIBFT		= ./libft/libft.a

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) $(FILES) $(LIBSLD) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(NAME)
	clear

fclean: clean

re: fclean all