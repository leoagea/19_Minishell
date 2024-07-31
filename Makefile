RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
ORANGE=\033[38;2;255;165;0m
NC=\033[0m

ifeq ($(ARCH),arm64)
READLIB = /opt/homebrew/opt/readline/lib
READINC = /opt/homebrew/opt/readline/include
else
READLIB = /Users/$(shell whoami)/homebrew/opt/readline/lib
READINC = /Users/$(shell whoami)/homebrew/opt/readline/include
endif

LINK = -L$(READLIB) -I$(READINC) -lreadline

NAME = minishell

DEBUG = debug

LIBFT = lib/libft.a

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS_DIR = src/
OBJS_DIR = obj/
DEBUG_DIR = obj_debug/

SRCS =	src/minishell.c \
	src/builtins/env.c src/builtins/pwd.c src/builtins/unset.c src/builtins/builtin.c src/builtins/echo.c \
	src/builtins/export/export.c src/builtins/export/export_functions.c src/builtins/export/export_sort.c \
	src/builtins/cd/cd.c src/builtins/cd/cd_functions.c src/builtins/exit.c \
	src/signals/signals.c \
	src/exec/redirections.c src/exec/pipe.c src/exec/heredoc.c src/exec/pipe_utils.c \
	src/lexer/tokens.c src/lexer/utils.c src/lexer/check.c src/lexer/check_2.c \
	src/parser/cmd.c src/parser/utils_cmd.c src/parser/redirections.c \
	src/expander/expander.c src/expander/env_variable.c src/expander/double_quotes.c src/expander/single_quotes.c  src/expander/heredoc.c src/expander/check.c src/expander/sweep_word.c \
	src/utils/init.c src/utils/free.c src/utils/init_env.c src/utils/lst.c src/utils/free_var.c \
	

OBJ = $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

OBJD = $(SRCS:$(SRCS_DIR)%.c=$(DEBUG_DIR)%.o)

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
	@$(CC) $(OBJ) $(CFLAGS) $(LIBFT) $(LINK) -o $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/builtins
	@mkdir -p $(OBJS_DIR)/builtins/export
	@mkdir -p $(OBJS_DIR)/builtins/cd
	@mkdir -p $(OBJS_DIR)/signals
	@mkdir -p $(OBJS_DIR)/lexer
	@mkdir -p $(OBJS_DIR)/exec
	@mkdir -p $(OBJS_DIR)/parser
	@mkdir -p $(OBJS_DIR)/expander
	@mkdir -p $(OBJS_DIR)/utils
	@$(CC) -o $@ -c $<

$(DEBUG_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(DEBUG_DIR)
	@mkdir -p $(DEBUG_DIR)/builtins
	@mkdir -p $(DEBUG_DIR)/builtins/export
	@mkdir -p $(DEBUG_DIR)/builtins/cd
	@mkdir -p $(DEBUG_DIR)/signals
	@mkdir -p $(DEBUG_DIR)/lexer
	@mkdir -p $(DEBUG_DIR)/exec
	@mkdir -p $(DEBUG_DIR)/parser
	@mkdir -p $(DEBUG_DIR)/expander
	@mkdir -p $(DEBUG_DIR)/utils
	@$(CC)  -o $@ -c $<

$(LIBFT):
	@echo "$(YELLOW)Compiling Libft...$(NC)"
	@make -C libft/

debug : $(LIBFT) $(OBJD)
	@make -C libft
	@$(CC) $(OBJD) $(CFLAGS) -fsanitize=address -g $(LIBFT) $(LINK) -o $(DEBUG)

clean :
	@make clean -C libft
	@$(RM) obj/**/*.o
	@$(RM) obj_debug/**/*.o
	@$(RM) obj/minishell.o
	@$(RM) obj_debug/minishell.o

fclean : clean
	@make fclean -C libft
	@$(RM) lib/
	@$(RM) $(NAME)

exec :
	@rm -rf /Users/vdarras/homebrew/bin/minishell
	@cp minishell /Users/vdarras/homebrew/bin

re : fclean all exec
	@$(RM) $(DEBUG)
 
