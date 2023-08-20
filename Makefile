# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpasztor <gpasztor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/12 21:35:02 by ffederol          #+#    #+#              #
#    Updated: 2023/08/20 11:13:21 by gpasztor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

OBJDIR	= mandatory/obj/
SRCDIR	= mandatory/src/
INCDIR 	= -I ./include 
LIBFT   = ./lib/libft/libft.a
LIBMLX42_DIR = ./lib/MLX42/build/
LIBMLX42 = $(LIBMLX42_DIR)libmlx42.a

MAIN	=	cub3d \
			movement \
			
PARSER		=	parser/parser \
				parser/parser_utils

RAYCASTER	=	raycaster/raycaster \
				raycaster/ray_calculations

GRAPHICS	=	graphics/graphics \
				graphics/draw_texture \

SOURCE		= $(MAIN) $(PARSER) $(RAYCASTER) $(GRAPHICS)

SRC	= $(addprefix $(SRCDIR), $(addsuffix .c, $(SOURCE)))
OBJ	= $(addprefix $(OBJDIR), $(addsuffix .o, $(SOURCE)))

CC		= cc
RMF		= rm -f
RMRF	= rm -rf
RMDIR	= rmdir
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address -Ofast 
FFLAGS	= -lglfw 

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

$(NAME): libmake $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBFT) $(LIBMLX42) -o $(NAME) $(FFLAGS)

libmake:
	git submodule update --init --recursive --remote
	$(MAKE) all bonus -C ./lib/libft
	@cd lib/MLX42 && cmake -B build && cmake --build build -j4
	# curl https://icanhazdadjoke.com/

clean:
	$(RMRF) $(OBJ)
	$(RMRF) $(OBJDIR)
	$(RMRF) $(LIBMLX42_DIR)
	@make clean -C ./lib/libft

fclean: clean
	$(RMF) $(NAME)
	make fclean -C ./lib/libft
	@rm -f ./lib/MLX42/build/libmlx42.a
	
re: fclean all

all: $(NAME)

.PHONY: all clean fclean re libmake
