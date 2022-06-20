# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 23:16:18 by mmeising          #+#    #+#              #
#    Updated: 2022/06/20 02:06:08 by lkindere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# gcc main.c libmlx42.a -lglfw -L "/Users/$USER/.brew/opt/glfw/lib" -I ./include/

VPATH = src src/parse src/player src/rays src/math src/draw

NAME := ./cub3d
LIBFT_PATH := ./libs/libft/
LIBFT := $(LIBFT_PATH)libft.a
MLX_PATH := ./libs/MLX42/
MLX := $(MLX_PATH)libmlx42.a

# CFLAGS ?= -Wall -Werror -Wextra

SRC_M :=	main.c						\
			utils.c						\
			init.c						\
			hooks.c						\
			rotate.c					\
			do_rays.c					\
			movement.c					\
			collision.c					\
			vector.c 					\
			draw.c						\
			draw_rays.c					\

PARSE_S := 	parser.c					\
			inits.c 					\
			get_textures.c 				\
			get_colors.c 				\
			get_map.c 					\
			check_map.c 				\
			check_walls.c 				\
			utils.c						\
			ft_is.c 					\
			ft_join_free.c 				\


OBJ_DIR := ./_obj
OBJ_DIR_DEBUG := ./_obj_debug

SRC := $(SRC_M) $(PARSE_S)
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_DEBUG := $(addprefix $(OBJ_DIR_DEBUG)/, $(SRC:.c=.o))

LIB := -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib" ./libs/MLX42/libmlx42.a -lm
INC := -I ./include -I ./libs/MLX42/include/MLX42/ -I ./libs/libft/header/

# Colorcodes
Y := "\033[33m"
R := "\033[31m"
G := "\033[32m"
B := "\033[34m"
X := "\033[0m"
UP := "\033[A"
CUT := "\033[K"

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	$(CC) $(CFLAGS) $^ $(LIBFT) $(LIB) -o $(NAME)
	@echo $(G)Finished"  "[$(NAME)]...$(X)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p _obj
	@$(CC) $(CFLAGS) -MMD -MP -c $< $(INC) -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

$(MLX):
	make -C $(MLX_PATH)

clean:
	make clean -C $(LIBFT_PATH)
	@if [ -d "${OBJ_DIR}" ]; then \
		echo $(R)Cleaning"  "[$(OBJ_DIR)]...$(X); \
		rm -r ${OBJ_DIR}; \
		echo $(G)Cleaned!$(X); \
	fi

clean_debug:
	@if [ -d "${OBJ_DIR_DEBUG}" ]; then \
		echo $(R)Cleaning"  "[$(OBJ_DIR_DEBUG)]...$(X); \
		rm -r ${OBJ_DIR_DEBUG}; \
		echo $(G)Cleaned!$(X); \
	fi

fclean: clean clean_debug
	make fclean -C $(LIBFT_PATH)
	@if [ -f "$(NAME)" ]; then \
		echo $(R)Cleaning"  "[$(NAME)]...$(X); \
		rm -r $(NAME); \
		echo $(G)Cleaned!$(X); \
	fi

re: fclean all

debug: $(OBJ_DEBUG) $(LIBFT)
	$(CC) $(CFLAGS) -g $^ $(LIBFT) $(LIB) -o debug
	lldb debug

$(OBJ_DIR_DEBUG)/%.o: %.c
	@mkdir -p _obj_debug
	@$(CC) $(CFLAGS) -g -MMD -MP -c $< $(INC) -o $@

.PHONY: all clean fclean re debug

-include $(OBJ:.o=.d)