# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lagea <lagea@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/06 01:08:23 by lagea             #+#    #+#              #
#    Updated: 2024/06/24 13:33:59 by lagea            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
ORANGE=\033[38;2;255;165;0m
NC=\033[0m 

NAME		= minishell

SRC_DIR		= src/
OBJ_DIR		= obj/
INC_DIR		= includes/
BUILT_DIR   = builtins/
SIGNAL_DIR  = signals/

SRC_BUILT		= $(wildcard $(BUILT_DIR)*.c) 
SRC_SIGNAL		= $(wildcard $(SIGNAL_DIR)*.c) 
OBJ_BUILT		= $(SRC:$(SRC_DIR/BUILT_DIR)%.c=$(OBJ_DIR/BUILT_DIR)%.o)
OBJ_SIGNAL		= $(SRC:$(SRC_DIR/SIGNAL_DIR)%.c=$(OBJ_DIR/SIGNAL_DIR)%.o)

LIBFT 		= lib/libft.a
LIBFT_PATH 	= libft/

CC			= gcc
RM			= rm -f
C_FLAGS		= -Wall -Wextra -Werror
INCS 		= -I$(INC_DIR) -I.

TOTAL_FILES 	:= $(words $(SRC))
CURRENT_FILE 	:= 0

define progress_bar_minishell
    @$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
    @printf "\r$(YELLOW)Compiling Minishell ... [%-$(TOTAL_FILES)s] %d/%d $(NC)" $$(for i in $$(seq 1 $(CURRENT_FILE)); do printf "#"; done) $(CURRENT_FILE) $(TOTAL_FILES)
	@if [ $(CURRENT_FILE) -eq $(TOTAL_FILES) ]; then echo ""; fi
endef

TOTAL_FILES 	:= $(words $(wildcard $(SRC_DIR)*.c))
CURRENT_FILE 	:= 0


$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BUILT_DIR)
	@mkdir -p $(SIGNAL_DIR)
	@$(CC) $(C_FLAGS) $(INCS) -Imlx -c $< -o $@
	$(call progress_bar_minishell)

all: $(LIBFT) $(NAME)


$(NAME): $(LIBFT) $(OBJ)
	@echo "$(GREEN)Linking objects to create executable...$(NC)"
	@$(CC) $(OBJ) $(LIBFT) $(LIB) $(MLX) -o $(NAME)
	@echo "$(BLUE)Executable $(NAME) created!$(NC)"
	
$(LIBFT):
	@echo "$(YELLOW)Compiling Libft...$(NC)"
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@echo "$(ORANGE)Cleaning objects for Libft...$(NC)"
	@$(MAKE) clean -C $(LIBFT_PATH) > /dev/null
	@echo "$(GREEN)Cleaned objects Libft!$(NC)"
	@echo "$(ORANGE)Cleaning objects for Minishell...$(NC)"
	@$(RM) $(OBJ_DIR)*.o
	@echo "$(GREEN)Cleaned Minishell objects!$(NC)"

fclean: clean
	@echo "$(ORANGE)Fully cleaning library for Libft...$(NC)"
	@$(MAKE) fclean -C $(LIBFT_PATH) > /dev/null
	@echo "$(BLUE)Fully cleaned Libft!$(NC)"
	@echo "$(ORANGE)Fully cleaning library for Minishell...$(NC)"
	@$(RM) $(NAME) 
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(OBJB_DIR)
	@echo "$(BLUE)Fully cleaned Minishell!$(NC)"

re: fclean all

.PHONY: all clean fclean re