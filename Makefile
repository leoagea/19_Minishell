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

SRCS_DIR = src/
OBJS_DIR = obj/

SRCS =	src/minishell.c \
	src/builtins/env.c \
	src/lexer/tokens.c src/lexer/utils.c src/lexer/check.c \
	src/parser/cmd.c src/parser/utils_cmd.c src/parser/redirections.c \
	src/expander/expander.c src/expander/env_variable.c src/expander/double_quotes.c src/expander/single_quotes.c \
	src/utils/init.c \
	

OBJ = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ)
	@make -C libft
	@printf "                                               \r"
	@echo "                 					"
	@echo "   	 ███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗      "
	@echo "  	 ████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║      "
	@echo " 	 ██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║ █████╗   ██║      ██║      "
	@echo " 	 ██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║ ██╔══╝   ██║      ██║      "
	@echo " 	 ██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║ ███████╗ ███████╗ ███████╗ "
	@echo " 	 ╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝ "
	@echo "                 					"
	@$(CC) $(OBJ) $(LIBFT) $(CFLAGS) -lreadline -g -o $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/builtins
	@mkdir -p $(OBJS_DIR)/signals
	@mkdir -p $(OBJS_DIR)/lexer
	@mkdir -p $(OBJS_DIR)/parser
	@mkdir -p $(OBJS_DIR)/expander
	@mkdir -p $(OBJS_DIR)/utils
	@$(CC) -o $@ -c $<

$(LIBFT):
	@echo "$(YELLOW)Compiling Libft...$(NC)"
	@make -C libft/

clean :
	@make clean -C libft
	@$(RM) obj/**/*.o
	@$(RM) obj/minishell.o

fclean : clean
	@make fclean -C libft
	@$(RM) lib/
	@$(RM) $(NAME)

re : fclean all