# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 23:16:18 by mmeising          #+#    #+#              #
#    Updated: 2022/06/13 21:23:25 by mmeising         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# gcc main.c libmlx42.a -lglfw -L "/Users/$USER/.brew/opt/glfw/lib" -I ./include/

VPATH = src

NAME := ./cub3d
LIBFT_PATH := ./libs/libft/
LIBFT := $(LIBFT_PATH)libft.a

CFLAGS ?= -Wall -Werror -Wextra

SRC_M :=								\
			main.c						\
			utils.c						\
			init.c						\

OBJ_DIR := ./_obj
OBJ_DIR_DEBUG := ./_obj_debug

SRC := $(SRC_M) 
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_DEBUG := $(addprefix $(OBJ_DIR_DEBUG)/, $(SRC:.c=.o))

LIB := -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib" ./libs/MLX42/libmlx42.a
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

# only need to link the readline libraries for the executable with $(LIB)
$(NAME): $(OBJ) $(LIBFT)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	$(CC) $(CFLAGS) $^ $(LIBFT) $(LIB) -o $(NAME)
	@echo $(G)Finished"  "[$(NAME)]...$(X)

# only need the header files for the object file compilation
$(OBJ_DIR)/%.o: %.c
	@mkdir -p _obj
	@$(CC) $(CFLAGS) -MMD -MP -c $< $(INC) -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
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