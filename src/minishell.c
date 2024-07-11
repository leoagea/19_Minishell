/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/07/11 14:44:26 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int agc, char **argv, char **envp)
{
	
	char *input;
    char *str;
    char check;
    t_data data;

    g_exit_status = 0;
    data.lexer = dll_init();
    data.parser = dll_cmd_init();
    data.env = init_env(envp);
    // Print a prompt and read a line of input from the user
    while (1)
    {
        data.input = readline("\nminishell$ ");

        // If the input is not NULL, print it and free the allocated memory
        if (ft_strncmp(data.input, "\0", 1) == 0)
            continue;
        if (data.input) {
            
            str = ft_strdup(data.input);
            add_history(str);
            
            if (lexer(str, data.lexer))
                return 1;
           
            // printf("---------------\nLexer\n");
            // dll_print_forward(data.lexer);
            // printf("---------------\n");
            expander(&data);
           
            // printf("---------------\nExpander\n");
            // dll_print_forward(data.expander);
            // printf("---------------\n");
            parser(&data);
            // dll_cmd_print_forward(data.parser);
            
            dll_clear(data.lexer);
            data.lexer->head = NULL;
            data.lexer->tail = NULL;
            free(data.input);
            free(str);
        }
    }
	return 0;
}

//expand cas particulier heredoc
//virer les " " et les ' '
//pas expand les env var