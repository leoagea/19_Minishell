/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:10:37 by vdarras           #+#    #+#             */
/*   Updated: 2024/07/03 18:15:51 by lagea            ###   ########.fr       */
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

typedef struct s_cmd
{
    char                    **str; //cmd, arg, flag
    // int                        (builtin)(t_data , struct s_cmd);
    int                        num_redirections;
    t_node                    *redirections;
    struct s_cmd    *next;
    struct s_cmd    *prev;
}                t_cmd;

typedef struct s_data
{
	char *input;
	t_dll *lexer;
	t_cmd *parser;
}				t_data;

/*-------------------------------Minishell----------------------------------*/

t_dll	*dll_init(void);

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

/*-------------------------------PARSER----------------------------------*/
/*--------------------------------Cmd------------------------------------*/

int parser(t_data *data);

#endif