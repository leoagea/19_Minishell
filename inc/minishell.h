/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:10:37 by vdarras           #+#    #+#             */
/*   Updated: 2024/07/14 23:54:55 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdbool.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>

# define BUFFER_SIZE 10000

int   g_exit_status;

int g_exit_status;

typedef enum s_bool
{
	FALSE, //  0
	TRUE   //  1
}					t_bool;

typedef struct s_env
{
   char *var;
   char *value;
   int				flag;
	struct s_env	*next; 
}              t_env;

typedef struct s_lst
{
	struct s_env	*head;
	struct s_env	*tail;
}					t_lst;

typedef struct s_cmd
{
   char                    **str; //cmd, arg, flag
   bool                    is_builtin;
   int                     num_redirections;
	char					      **env;
   char                    *absolute_path;
   t_dll                   *redirections;
   t_lst                  *env_list;
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
    int end;
    int sub;
    int start;
    int var_len;
    char *var;
    char *expand;
}               t_env_expand;

typedef struct s_data
{
	char *input;
   t_lst *env;
	t_dll *lexer;
   t_dll *expander;
	t_dll_cmd *parser;
   t_env_expand *env_expand;
}				t_data;

	//// MAIN ////
	//MINISHELL//

//// BUILTINS ////

   //UNSET//
void    del_node(t_list **node, char *str);
int     count_to_equal(char *str);
void    unset(t_list **env, t_list **export, char *var);

   //CD//
void	cd(t_list **env, t_list **export);

//// SIGNALS ////
	//CTRL C//
void    rl_replace_line(const char *text, int clear_undo);
void	reset_ctrl_C(int sig);
void	reset_ctrl_slash(int sig);
void	handle_signal(void);


//// EXEC ////
  // REDIRECTIONS //
void    redirections(t_cmd *command);

  // EXEC_PIPE //
void    exec_pipe(t_cmd *command);

//// UTILS ////
   //FREE//
int     length_array_char(char **array);
void  free_tab_char(char **array);

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
bool check_open_quote(const char *str);
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

char *join_char(char *str, char c);
int expander(t_data *data);

/*------------------------------heredoc----------------------------------*/

char *expand_heredoc(char *str);

/*---------------------------env_variables-------------------------------*/

char *handle_env_variables(t_data *data, char *str, int i);
char *expand_env_var(t_data *data, char *cpy, int *i, char *str);

/*---------------------------double_quotes-------------------------------*/

char *expand_double_quotes(t_data *data, char *cpy, int *i, char *str);

/*---------------------------single_quotes-------------------------------*/

char *expand_single_quotes(char *cpy, int *i, char *str);

/*-------------------------------check-----------------------------------*/

void check_node_null(t_data *data);

/*--------------------------------UTILS----------------------------------*/
/*--------------------------------init-----------------------------------*/

t_dll	*dll_init(void);
t_dll_cmd *dll_cmd_init(void);
t_env_expand *env_var_init(void);
t_lst *lst_init(void);

/*------------------------------init_env---------------------------------*/

t_lst	*init_env(char **envp);

/*--------------------------------lst------------------------------------*/

t_env	*lst_new(char *var, char *value, int flag);
void	lst_insert_tail(t_env *new, t_lst *lst);
int    lst_size(t_lst *lst);

/*------------------------------BUILTINS---------------------------------*/
/*--------------------------------echo-----------------------------------*/

void echo(t_cmd *cmd);

/*--------------------------------echo-----------------------------------*/

char *get_pwd(void);

/*--------------------------------env------------------------------------*/

void	print_env(t_lst *env);

/*--------------------------------pwd------------------------------------*/

int		pwd(void);

/*-------------------------------export-----------------------------------*/

void	print_export(t_lst *env);
int export(t_data *data, t_cmd *cmd);

/*--------------------------export_functions-------------------------------*/

int export_var(t_data *data, char *str);
int export_var_value(t_data *data, char *str);
int export_cat_value(t_data *data, char *str);
void sort_export(char **arr, int size);

#endif