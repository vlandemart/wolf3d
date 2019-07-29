#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: njacobso <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/19 16:28:47 by njacobso          #+#    #+#              #
#    Updated: 2019/07/30 00:35:23 by ydavis           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC			= gcc
NAME		= wolf3d
CFLAGS		= -o3 -Wall -Werror -Wextra -F ~/Library/Frameworks -framework SDL2\
			  -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers
INCLUDES	= include
SRC			= args.c collisions.c defines.c degrad.c drawing.c events.c\
			  floorceil.c init.c main.c map_help.c movement.c objects.c\
			  ray_help.c raycast.c read_map.c rgb_manipulations.c system.c\
			  textures.c time.c turn.c update.c vectors.c walls.c player_find.c
OBJ			= args.o collisions.o defines.o degrad.o drawing.o events.o\
			  floorceil.o init.o main.o map_help.o movement.o objects.o\
			  ray_help.o raycast.o read_map.o rgb_manipulations.o system.o\
			  textures.o time.o turn.o update.o vectors.o walls.o player_find.o
LIBFT		= lib/libft

all: $(NAME)

$(NAME):	$(LIBFT) $(SRC) $(HDR)
	@cp -r SDL2.framework ~/Library/Frameworks/
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
