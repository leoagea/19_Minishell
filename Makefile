RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
ORANGE=\033[38;2;255;165;0m
NC=\033[0m

NAME = minishell

LIBFT = lib/libft.a

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS = src/builtins/env.c

OBJS = $(SRCS:.c=.o)

OBJS_DIR = ./obj

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C libft
	@printf "                                               							   \r"
	@echo "\033[0;34m                 																 "
	@echo "\033[0;34m    	 ███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗      "
	@echo "\033[0;34m  	 ████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║      "
	@echo "\033[0;34m 	 ██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║ █████╗   ██║      ██║      "
	@echo "\033[0;34m 	 ██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║ ██╔══╝   ██║      ██║      "
	@echo "\033[0;34m 	 ██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║ ███████╗ ███████╗ ███████╗ "
	@echo "\033[0;34m 	 ╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝ "
	@echo "\033[0;34m                 																 "
	@$(CC) $(OBJS) $(LIBFT) -g -o $(NAME)

$(OBJS_DIR)%.o : ./src%.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/builtins
	@mkdir -p $(OBJS_DIR)/signals
	@$(CC) -o $@ -c $<

fclean : clean
	@make fclean -C libft
	@$(RM) $(NAME)

clean :
	@make clean -C libft
	@$(RM) obj/*.o src/builtins/*.o obj/signals/*.o ./lib ./obj

re : fclean all