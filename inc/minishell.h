/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:10:37 by vdarras           #+#    #+#             */
/*   Updated: 2024/07/02 16:06:33 by lagea            ###   ########.fr       */
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

typedef enum s_bool
{
	FALSE, //  0
	TRUE   //  1
}					t_bool;

// typedef enum s_type
// {
// 	INPUT = 1, // '<'                              0
// 	TRUNC,     // '>'                              1
// 	HEREDOC,   // '<<'                             2
// 	APPEND,    // '>>'                             3
// 	PIPE,      // '|'                              4
// 	CMD,       // 'COMMAND'  (cat, ls, ...)        5
// 	OPTION,    // 'OPTION'   (-n, -la, ...)        6
// 	ARG        // 'ARGUMENT DE COMMANDE' (Ce qu'il y a apres une commande comme echo par exemple,entre quotes ou non) 7
// }					t_type;

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
	char			**command; 	// complete command : array of string to passs in execve
}					t_command;

/*--------------------------------LEXER----------------------------------*/
/*-------------------------------Tokens----------------------------------*/

int lexer(char *input, t_dll *tokens);

/*--------------------------------Utils----------------------------------*/

int	check_whitespace(char *str, int i);
int check_special_char(char *str, int i);

#endif