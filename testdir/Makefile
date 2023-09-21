# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffederol <ffederol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/12 21:35:02 by ffederol          #+#    #+#              #
#    Updated: 2023/09/21 22:05:03 by ffederol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D


INCDIR 	= -I ./include 
LIBFT   = ./lib/libft/libft.a

MAIN	=	cub3d	

PARSER		=	parser/parser			\
				parser/parser_utils		\
				parser/parser_validity	\
				parser/parser_sorting	\
				parser/parser_sort_type


SOURCE		= $(MAIN) $(PARSER) 

SRC	= $(addprefix $(SRCDIR), $(addsuffix .c, $(SOURCE)))
OBJ	= $(addprefix $(OBJDIR), $(addsuffix .o, $(SOURCE)))

CC		= cc
RMF		= rm -f
RMRF	= rm -rf
RMDIR	= rmdir
CFLAGS	= -Wall -Wextra -Werror -Ofast


%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

$(NAME): libmake $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBFT)  -o $(NAME) $(FFLAGS)

libmake:
	$(MAKE) all bonus -C ./lib/libft

clean:
	$(RMRF) $(OBJ)
	$(RMRF) $(OBJDIR)
	@make clean -C ./lib/libft

fclean: clean
	$(RMF) $(NAME)
	make fclean -C ./lib/libft
	
re: fclean all

all: $(NAME)

.PHONY: all clean fclean re libmake