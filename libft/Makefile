# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lagea <lagea@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 16:07:15 by lagea             #+#    #+#              #
#    Updated: 2024/07/29 12:55:27 by lagea            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
ORANGE=\033[38;2;255;165;0m
NC=\033[0m

NAME = libft.a

SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = inc/
LIB_DIR = ../lib/
LIBNAME = $(LIB_DIR)$(NAME)

SRC = src/original/ft_atoi.c src/original/ft_bzero.c src/original/ft_calloc.c src/original/ft_isalnum.c src/original/ft_isalpha.c \
		src/original/ft_isascii.c src/original/ft_isdigit.c src/original/ft_isprint.c src/original/ft_memchr.c \
		src/original/ft_memcmp.c src/original/ft_memcpy.c src/original/ft_memmove.c src/original/ft_memset.c src/original/ft_strchr.c \
		src/original/ft_strdup.c src/original/ft_strlcat.c src/original/ft_strlcpy.c src/original/ft_strlen.c src/original/ft_strncmp.c \
		src/original/ft_strnstr.c src/original/ft_strrchr.c src/original/ft_tolower.c src/original/ft_toupper.c \
		src/original/ft_substr.c src/original/ft_strjoin.c src/original/ft_split.c src/original/ft_itoa.c \
		src/original/ft_putchar_fd.c src/original/ft_putstr_fd.c src/original/ft_putendl_fd.c \
		src/original/ft_putnbr_fd.c src/original/ft_strtrim.c src/original/ft_striteri.c src/original/ft_strmapi.c \
		src/original/ft_lstnew_bonus.c src/original/ft_lstadd_front_bonus.c src/original/ft_lstadd_back_bonus.c \
		src/original/ft_lstlast_bonus.c src/original/ft_lstclear_bonus.c src/original/ft_lstdelone_bonus.c \
		src/original/ft_lstmap_bonus.c src/original/ft_lstsize_bonus.c src/original/ft_lstiter_bonus.c \
		src/printf/printf.c src/printf/parse.c src/printf/print_elements.c src/printf/print_elements_2.c src/printf/utils_len.c \
		src/get_next_line/get_next_line.c src/get_next_line/get_next_line_utils.c \
		src/added_funct/ft_atol.c src/added_funct/ft_atoi_base.c src/added_funct/ft_putunbr_fd.c src/added_funct/ft_realloc.c \
		src/double_linked_list/dll_insert_head.c src/double_linked_list/dll_insert_tail.c src/double_linked_list/dll_new_node.c \
		src/double_linked_list/dll_print_forward.c src/double_linked_list/dll_size.c src/double_linked_list/dll_clear.c \
		src/double_linked_list/dll_delete_head.c src/double_linked_list/dll_delete_tail.c src/double_linked_list/dll_print_backward.c \

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

CC = gcc
RM	= rm -rf
CFLAGS = -Wall -Wextra -Werror
INCS = -I$(INC_DIR) -I.

TOTAL_FILES 	:= $(words $(SRC))
CURRENT_FILE 	:= 0

define progress_bar_push_swap
    @$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
    @printf "\r$(YELLOW)Compiling Libft... [%-$(TOTAL_FILES)s] %d/%d $(NC)" $$(for i in $$(seq 1 $(CURRENT_FILE)); do printf "#"; done) $(CURRENT_FILE) $(TOTAL_FILES)
	@if [ $(CURRENT_FILE) -eq $(TOTAL_FILES) ]; then echo ""; fi
endef

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/added_funct
	@mkdir -p $(OBJ_DIR)/double_linked_list
	@mkdir -p $(OBJ_DIR)/get_next_line
	@mkdir -p $(OBJ_DIR)/get_next_line_linked_list
	@mkdir -p $(OBJ_DIR)/original
	@mkdir -p $(OBJ_DIR)/printf
	@$(CC) $(CFLAGS) $(INCS) -g -c $< -o $@
	$(call progress_bar_push_swap)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Creating libft library $(LIBNAME)...$(NC)"
	@mkdir -p $(LIB_DIR)
	@ar rc $(LIBNAME) $(OBJ)
	@echo "$(BLUE)Library libft created!$(NC)"
	
clean:
	@echo "$(ORANGE)Cleaning objects libft...$(NC)"
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)Cleaned objects libft!$(NC)"

fclean: clean
	@echo "$(ORANGE)Fully cleaning libft...$(NC)"
	@$(RM) $(LIBNAME)
	@echo "$(BLUE)Fully cleaned libft!$(NC)"

re: fclean all

.PHONY: all clean fclean re