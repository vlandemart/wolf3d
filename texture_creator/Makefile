# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydavis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/30 00:36:21 by ydavis            #+#    #+#              #
#    Updated: 2019/07/30 00:38:26 by ydavis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc
NAME		= creator
CFLAGS		= -o3 -Wall -Werror -Wextra -F ~/Library/Frameworks -framework SDL2\
			  -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers
INCLUDES	= include
SRC			= creator_help.c defines.c events.c export.c help_create.c\
			  texture_creator.c
OBJ			= creator_help.o defines.o events.o export.o help_create.o\
			  texture_creator.o
LIBFT		= lib/libft

all: $(NAME)

$(NAME):	$(LIBFT) $(SRC) $(HDR)
	@cp -r ../SDL2.framework ~/Library/Frameworks/
	@make --directory=$(LIBFT)
	@$(CC) $(CFLAGS) $(SRC) lib/libft/libft.a -o $(NAME)

clean:
	@rm -rf $(OBJ)
	@rm -rf ~/Library/Frameworks/SDL.framework
	@make --directory=$(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make --directory=$(LIBFT) fclean

re: fclean all
