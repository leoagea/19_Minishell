/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:10:37 by vdarras           #+#    #+#             */
/*   Updated: 2024/07/18 18:12:23 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define BUFFER_SIZE 10000

int					g_exit_status;

typedef struct s_env
{
	char			*var;
	char			*value;
	int				flag;
	struct s_env	*next;
}					t_env;

typedef struct s_lst
{
	struct s_env	*head;
	struct s_env	*tail;
}					t_lst;

typedef struct s_cmd
{
	char			**str;
	bool			is_builtin;
	int				num_redirections;
	char			**env;
	char			*absolute_path;
	t_dll			*redirections;
	t_lst			*env_list;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_dll_cmd
{
	struct s_cmd	*head;
	struct s_cmd	*tail;
}					t_dll_cmd;

typedef struct s_env_expand
{
	int				end;
	int				sub;
	int				start;
	int				var_len;
	char			*var;
	char			*expand;
}					t_env_expand;

typedef struct s_data
{
	char			*input;
	char 			**env_arr;
	t_lst			*env;
	t_dll			*lexer;
	t_dll			*expander;
	t_dll_cmd		*parser;
	t_env_expand	*env_expand;
}					t_data;

//// MAIN ////
// MINISHELL//

//// SIGNALS ////
// CTRL C//
void 				rl_clear_history (void);
void				rl_replace_line(const char *text, int clear_undo);
void				reset_ctrl_c(int sig);
void				reset_ctrl_slash(int sig);
void				handle_signal(void);

//// EXEC ////
// REDIRECTIONS //
void				redirections(t_cmd *command);

// EXEC_PIPE //
void				exec_pipe(t_cmd *command, t_data *data);


/*==============================Minishell================================*/

/*================================LEXER==================================*/
/*-------------------------------tokens----------------------------------*/

int					lexer(char *input, t_dll *tokens);

/*--------------------------------ttils----------------------------------*/

int					check_whitespace(char *str, int i);
int					check_special_char(char *str, int i);
int					skip_whitespace(char *str, int i);

/*--------------------------------check----------------------------------*/

int					check_open_pipe(t_dll *tokens);
bool				check_open_quote(const char *str);
int					check_open_redirect(t_dll *tokens);
int					check_wrong_token(t_dll *tokens);
int					do_all_check(t_dll *tokens);

/*-------------------------------check_2---------------------------------*/

int check_inside_pipe(t_dll *tokens);

/*===============================PARSER==================================*/
/*--------------------------------Cmd------------------------------------*/

int					parser(t_data *data);

/*----------------------------Redirections-------------------------------*/

int					handle_redirections(t_dll *single_cmd, t_data *data);

/*-----------------------------Utils_cmn---------------------------------*/

t_cmd				*dll_cmd_new_node(void);
void				dll_cmd_insert_tail(t_dll_cmd *dll, t_cmd *new);
void				dll_cmd_print_forward(t_dll_cmd *dll);
void				dll_delete_node(t_node *delete);
int					dll_cmd_size(t_dll_cmd *dll);

/*==============================EXPANDER=================================*/
/*------------------------------expander---------------------------------*/

char				*join_char(char *str, char c);
int					expander(t_data *data);

/*------------------------------heredoc----------------------------------*/

char				*expand_heredoc(char *str);

/*---------------------------env_variables-------------------------------*/

char				*handle_env_variables(t_data *data, char *str, int i);
char				*expand_env_var(t_data *data, char *cpy, int *i, char *str);

/*---------------------------double_quotes-------------------------------*/

char				*expand_double_quotes(t_data *data, char *cpy, int *i,
						char *str);

/*---------------------------single_quotes-------------------------------*/

char				*expand_single_quotes(char *cpy, int *i, char *str);

/*-------------------------------check-----------------------------------*/

void				check_node_null(t_data *data);

/*----------------------------sweep_word---------------------------------*/

char				*sweep_word(t_data *data, char *str);

/*================================UTILS==================================*/
/*--------------------------------init-----------------------------------*/

t_dll				*dll_init(void);
t_dll_cmd			*dll_cmd_init(void);
t_env_expand		*env_var_init(void);
t_lst				*lst_init(void);
int				init_shlvl(t_data *data);

/*------------------------------init_env---------------------------------*/

t_lst				*init_env(char **envp);

/*--------------------------------lst------------------------------------*/

t_env				*lst_new(char *var, char *value, int flag);
void				lst_insert_tail(t_env *new, t_lst *lst);
int					lst_size(t_lst *lst);
t_env				*get_node(t_lst *env, char *var);

/*-----------------------------free_var----------------------------------*/

void	free_str(char *str);
void	free_arr(char **arr);
void	free_lst(t_lst *lst);
int	free_var(const char *s, ...);

/*--------------------------------free-----------------------------------*/

void				dll_cmd_clear(t_dll_cmd *dll);
void		free_dll(t_dll *dll);
void		free_cmd(t_dll_cmd *cmd);
void		free_exp(t_env_expand *env);

/*==============================BUILTINS=================================*/
/*--------------------------------echo-----------------------------------*/

int					echo(t_cmd *cmd);

/*-------------------------------exit------------------------------------*/

int					ft_exit(t_data *data, t_cmd *simple_cmd);

/*--------------------------------env------------------------------------*/

void				print_env(t_lst *env);

/*--------------------------------pwd------------------------------------*/

char				*get_pwd(void);
int					pwd(void);

/*-------------------------------export-----------------------------------*/

int					export(t_data *data, t_cmd *cmd);

/*--------------------------export_functions-------------------------------*/

int					export_var(t_data *data, char *str);
int					export_var_value(t_data *data, char *str);
int					export_cat_value(t_data *data, char *str);

/*-----------------------------export_sort---------------------------------*/

void				sort_export(char **arr, int size);

/*--------------------------------unset------------------------------------*/

int					unset(t_data *data, t_cmd *cmd);

/*----------------------------------cd-------------------------------------*/

int					cd(t_data *data);

/*-----------------------------cd_functions--------------------------------*/

int					change_directory(t_data *data, char *new, char *old);

/*-------------------------------builtin-----------------------------------*/ 

void				is_builtin(t_cmd *command);
int					exec_builtin(t_cmd *command, t_data *data);

#endif