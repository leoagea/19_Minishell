/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:10:37 by vdarras           #+#    #+#             */
/*   Updated: 2024/07/08 18:56:30 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdbool.h>

int g_exit_status;

typedef enum s_bool
{
	FALSE, //  0
	TRUE   //  1
}					t_bool;

typedef struct s_cmd
{
    char                    **str; //cmd, arg, flag
    bool                    builtin;
    int                     num_redirections;
    t_dll                   *redirections;
    struct s_cmd    *next;
    struct s_cmd    *prev;
}                t_cmd;

typedef struct s_dll_cmd
{
    struct s_cmd *head;
    struct s_cmd *tail;
}               t_dll_cmd;

typedef struct s_env_expand
{
    int start;
    int end;
    char *var;
}               t_env_expand;

typedef struct s_data
{
	char *input;
    t_list *env;
	t_dll *lexer;
    t_dll *expander;
	t_dll_cmd *parser;
    t_env_expand *env_expand;
}				t_data;

/*------------------------------Minishell--------------------------------*/

/*--------------------------------LEXER----------------------------------*/
/*-------------------------------Tokens----------------------------------*/

int lexer(char *input, t_dll *tokens);

/*--------------------------------Utils----------------------------------*/

int	check_whitespace(char *str, int i);
int check_special_char(char *str, int i);
int skip_whitespace(char *str, int i);

/*--------------------------------Check----------------------------------*/

int check_open_pipe(t_dll *tokens);
int check_open_quote(char *str);
int	check_open_redirect(t_dll *tokens);
int check_wrong_token(t_dll *tokens);

/*-------------------------------PARSER----------------------------------*/
/*--------------------------------Cmd------------------------------------*/

int parser(t_data *data);

/*----------------------------Redirections-------------------------------*/

int handle_redirections(t_dll *single_cmd, t_data *data);

/*-----------------------------Utils_cmn---------------------------------*/

t_cmd	*dll_cmd_new_node(void);
void	dll_cmd_clear(t_dll_cmd *dll);
void	dll_cmd_insert_tail(t_dll_cmd *dll, t_cmd *new);
void	dll_cmd_print_forward(t_dll_cmd *dll);
void    dll_delete_node(t_node *delete);
int	    dll_cmd_size(t_dll_cmd *dll);

/*------------------------------EXPANDER---------------------------------*/
/*------------------------------expander---------------------------------*/

int expander(t_data *data);

/*---------------------------env_variables-------------------------------*/

char *handle_env_variables(t_data *data, char *str, int i);

/*--------------------------------UTILS----------------------------------*/
/*--------------------------------init-----------------------------------*/

t_dll	*dll_init(void);
t_dll_cmd *dll_cmd_init(void);
t_env_expand *env_var_init(void);
int		count_nodes(t_list *list);
t_list	*init_env(char **envp);

#endif