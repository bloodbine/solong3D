# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/12 21:35:02 by ffederol          #+#    #+#              #
#    Updated: 2023/08/12 22:18:09 by ffederol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

OBJDIR	= obj/
SRCDIR	= src/
INCDIR 	= -I ./include 
LIBFT   = ./lib/libft/libft.a

MAIN	=	cub3d.c

PARSER		=	

RAYCASTER	=	


SOURCE		= $(MAIN) $(PARSER) $(RAYCASTER)

SRC	= $(addprefix $(SRCDIR), $(addsuffix .c, $(SOURCE)))
OBJ	= $(addprefix $(OBJDIR), $(addsuffix .o, $(SOURCE)))

CC		= cc
RMF		= rm -f
RMRF	= rm -rf
RMDIR	= rmdir
CFLAGS	= -Wall -Wextra -Werror
FFLAGS	= -glfw 

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

$(NAME): libmake $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBFT) -o $(NAME) $(FFLAGS)

libmake:
	git submodule update --init --recursive --remote
	$(MAKE) all bonus -C ./lib/libft
	
	# curl https://icanhazdadjoke.com/

clean:
	$(RMRF) $(OBJ)
	$(RMRF) $(OBJDIR)

fclean: clean
	$(RMF) $(NAME)
	make fclean -C ./includes/libft

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re libmake
