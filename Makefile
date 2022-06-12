# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/05 20:10:21 by mmeising          #+#    #+#              #
#    Updated: 2022/06/12 20:19:56 by lkindere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH = utils

NAME := cube

CC := gcc
CFLAGS ?= -Wall -Werror -Wextra

PARSE_S :=	main.c				\
			parser.c 			\

UTILS :=	ft_atoi.c 			\
			ft_is.c 			\
			ft_join_free.c 		\
			ft_strncmp.c 		\

OBJ_DIR := ./_obj
OBJ_DIR_DEBUG := ./_obj_debug

SRC := $(PARSE_S) $(UTILS)
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_DEBUG := $(addprefix $(OBJ_DIR_DEBUG)/, $(SRC:.c=.o))

LIB := 
INC := -I ./

# Colorcodes
Y := "\033[33m"
R := "\033[31m"
G := "\033[32m"
B := "\033[34m"
X := "\033[0m"
UP := "\033[A"
CUT := "\033[K"

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	$(CC) $(CFLAGS) $^ $(LIB) -o $(NAME)
	@printf $(UP)$(CUT)
	@echo $(G)Finished"  "[$(NAME)]...$(X)

$(OBJ_DIR)/%.o: %.c
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p _obj
	@$(CC) $(CFLAGS) -MMD -MP -c $< $(INC) -o $@
	@printf $(UP)$(CUT)

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

debug: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -g $^ $(LIB) -o debug
	lldb debug

$(OBJ_DIR_DEBUG)/%.o: %.c
	@mkdir -p _obj_debug
	@$(CC) $(CFLAGS) -g -MMD -MP -c $< $(INC) -o $@

.PHONY: all clean fclean re debug

-include $(OBJ:.o=.d)