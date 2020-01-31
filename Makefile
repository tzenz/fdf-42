# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tzenz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/12 18:25:28 by tzenz             #+#    #+#              #
#    Updated: 2020/01/30 13:23:39 by tzenz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = srcs/fdf/*.c
SRC_DIR = srcs/fdf/

OBJ =   background.o\
        color.o\
        draw.o\
        key.o\
        main.o\
        menu.o\
        mouse.o\
        readfile.o\
        rotate.o\

LIB_INC_DIR = ./srcs/libft/include/
MLX_INC = ./srcs/minilibx_macos/
INC_DIR = ./includes/
INC = color.h fdf.h
INCS = $(addprefix $(INC_DIR), $(INC))

INCLUDE_A = srcs/libft/libft.a\
			srcs/minilibx_macos/libmlx.a\

FLAGS = -Wall -Wextra -Werror -I $(LIB_INC_DIR) -I $(MLX_INC) -I $(INC_DIR)

SRC_LIBFT = ./srcs/libft/
LIB_OBJ = $(addprefix $(SRC_LIBFT), *.o)
LIB_INC = $(addprefix $(SRC_LIBFT), include/libft.h)
SRC_MINILIBX = srcs/minilibx_macos

MLX_DIR = ./srcs/minilibx_macos/
MLX_LIB = ./srcs/minilibx_macos/libmlx.a/

OBJ_LIBFT = *.o\

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIB_OBJ) $(MLX_LIB) $(OBJ)
		@echo "fdf: $(GREEN)Creating fdf...$(RESET)"
		@gcc $(OBJ) $(INCLUDE_A) -o $(NAME) -framework OpenGL -framework AppKit

$(SRC_LIBFT)%.o: $(SRC_LIBFT)%.c $(LIB_INC)
		@echo "fdf: $(GREEN)Creating libft...$(RESET)"
		@make -C $(SRC_LIBFT)

%.o: $(SRC_DIR)%.c $(INCS)
		@gcc $(FLAGS) -c $<

$(MLX_DIR)%.a:
		@echo "fdf: $(GREEN)Creating minilibx...$(RESET)"
		@make -C $(SRC_MINILIBX)

clean:
		@echo "fdf: $(RED)Deleting libft obj...$(RESET)"
		@make clean -C $(SRC_LIBFT)
		@echo "fdf: $(RED)Deleting minilibx...$(RESET)"
		@make clean -C $(SRC_MINILIBX)
		@echo "fdf: $(RED)Deleting srcs obj...$(RESET)"
		@rm -f *.o

fclean: clean
		@echo "fdf: $(RED)Deleting libft.a...$(RESET)"
		@make fclean -C srcs/libft
		@echo "fdf: $(RED)Deleting ./fdf...$(RESET)"
		@rm -f $(NAME)

re: fclean clean all

.PHONY: all clean fclean re
