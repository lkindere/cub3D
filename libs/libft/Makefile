# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/01 20:26:16 by mmeising          #+#    #+#              #
#    Updated: 2022/06/11 17:05:04 by mmeising         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Makefile of outer project needs to include libft and its own header, so: 
#-I ./libft/header -I ./header

#-fsanitize=leak flag should be active in all Makefiles if needed

VPATH = src/char src/gnl src/io src/list src/memory src/string

NAME := libft.a

CC := gcc
CFLAGS ?= -Wall -Werror -Wextra

SRC_GNL := \
	get_next_line.c get_next_line_utils.c

SRC_CHAR := \
	ft_in_set.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_tolower.c ft_toupper.c

SRC_IO := \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c

SRC_LIST := \
	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c

SRC_MEMORY := \
	ft_bzero.c ft_calloc.c ft_free_c.c ft_free_i.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_2d_char_len.c ft_free_2d_char.c

SRC_STRING := \
	ft_atoi.c ft_itoa.c ft_split.c ft_strchr.c ft_strconcat.c ft_strdup.c \
	ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
	ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
	ft_substr.c

OBJ_DIR := ./_obj
OBJ_DIR_DEBUG := ./_obj_debug

SRC := $(SRC_GNL) $(SRC_CHAR) $(SRC_IO) $(SRC_LIST) $(SRC_MEMORY) $(SRC_STRING)
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

INC := -I ./header

OBJ_DEBUG := $(addprefix $(OBJ_DIR_DEBUG)/, $(SRC:.c=.o))

# Colorcodes
Y := "\033[33m"
R := "\033[31m"
G := "\033[32m"
B := "\033[34m"
X := "\033[0m"
UP := "\033[A"
CUT := "\033[K"

all: $(NAME)
	@printf "\n"
	@echo $(G)" __    _ _   ___ _   "
	@echo $(G)"|  |  |_| |_|  _| |_ "
	@echo $(G)"|  |__| | . |  _|  _|"
	@echo $(G)"|_____|_|___|_| |_|  "$(X)
	@printf "\n\n"

# only need to link the readline libraries for the executable with $(LIB)
$(NAME): $(OBJ)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	@ar -rcs $(NAME) $(OBJ)
	@printf $(UP)$(CUT)
	@echo $(G)Finished"  "[$(NAME)]...$(X)

# only need the header files for the object file compilation
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