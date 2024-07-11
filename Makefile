RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
ORANGE=\033[38;2;255;165;0m
NC=\033[0m

READLIB = /Users/$(shell whoami)/homebrew/opt/readline/lib
READINC = /Users/$(shell whoami)/homebrew/opt/readline/include
LINK = -L$(READLIB) -I$(READINC) -lreadline

NAME = minishell

LIBFT = lib/libft.a

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS_DIR = src/
OBJS_DIR = obj/

SRCS =	src/minishell.c \
	src/builtins/env.c src/builtins/export.c src/builtins/pwd.c src/builtins/unset.c src/builtins/cd.c src/builtins/builtin.c src/builtins/echo.c \
	src/signals/signals.c \
	src/exec/redirections.c src/exec/pipe.c src/exec/heredoc.c \
	src/lexer/tokens.c src/lexer/utils.c src/lexer/check.c \
	src/parser/cmd.c src/parser/utils_cmd.c src/parser/redirections.c \
	src/expander/expander.c src/expander/env_variable.c src/expander/double_quotes.c src/expander/single_quotes.c  src/expander/heredoc.c\
	src/utils/init.c src/utils/free.c \
	

OBJ = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ)
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
	@$(CC) $(OBJ) $(CFLAGS) $(LIBFT) -g $(LINK)  -o $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/builtins
	@mkdir -p $(OBJS_DIR)/signals
	@mkdir -p $(OBJS_DIR)/lexer
	@mkdir -p $(OBJS_DIR)/exec
	@mkdir -p $(OBJS_DIR)/parser
	@mkdir -p $(OBJS_DIR)/expander
	@mkdir -p $(OBJS_DIR)/utils
	@$(CC) $(CFLAGS) -o $@ -c $<

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