/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:10:37 by vdarras           #+#    #+#             */
/*   Updated: 2024/07/02 18:20:18 by vdarras          ###   ########.fr       */
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
# include <signal.h>

# define BUFFER_SIZE 10000

typedef enum s_bool
{
	FALSE, //  0
	TRUE   //  1
}					t_bool;

typedef enum s_type
{
	INPUT = 1, // '<'                              0
	TRUNC,     // '>'                              1
	HEREDOC,   // '<<'                             2
	APPEND,    // '>>'                             3
	PIPE,      // '|'                              4
	CMD,       // 'COMMAND'  (cat, ls, ...)        5
	OPTION,    // 'OPTION'   (-n, -la, ...)        6
	ARG       
		// 'ARGUMENT DE COMMANDE' (Ce qu'il y a apres une commande comme echo par exemple,entre quotes ou non) 7
}					t_type;

typedef struct s_tokens
{
	t_type type;    // C'est le type de token entre 0,1,2,...,6 enumere au dessus
	char *str;       // C'est la chaine de caractere literale
	struct s_tokens	*next;
}					t_tokens;

typedef struct s_command
{
	int 			infile;    		// fd infile
	int 			outfile;    	// fd outifile
	char			**command; 		// complete command : array of string to passs in execve
}					t_command;

	//// MAIN ////
	//MINISHELL//

//// BUILTINS ////
	//ENV//
int		count_nodes(t_list *list);
t_list	*init_env(char **envp);
void	print_env(t_list *env);

   //EXPORT//
char	*min_node(t_list *env);
t_list	*init_export(t_list	*env);
void	print_export(t_list *export);
void	export_node_0equal(t_list **export, char *str);
void	export_node_1equal(t_list **env, t_list **export, char *str);

   //PWD//
int		pwd(void);

   //UNSET//
void    del_node(t_list **node, char *str);
int     count_to_equal(char *str);
void    unset(t_list **env, t_list **export, char *var);

   //CD//
void	cd_home(t_list **env, t_list **export);

//// SIGNALS ////
	//CTRL C//
void    rl_replace_line(const char *text, int clear_undo);
void	reset_ctrl_C(int sig);
void	reset_ctrl_slash(int sig);
void	handle_signal(void);

#endif