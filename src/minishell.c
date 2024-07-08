/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/07/08 19:15:54 by lagea            ###   ########.fr       */
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
        data.input = readline("minishell$ ");

        // If the input is not NULL, print it and free the allocated memory
        if (ft_strncmp(data.input, "\0", 1) == 0)
            continue;
        if (data.input) {
            
            str = ft_strdup(data.input);
            add_history(str);
            
            if (lexer(str, data.lexer))
                return 1;
            parser(&data);
            printf("------------------\n");
            // dll_cmd_print_forward(data.parser);
            
            //print the **arr give to the exec
            // t_cmd *current;
            // char **arr;
            // int i;
            
            // current = data.parser->head;
            // while (current != NULL){
            //     arr = current->str;
            //     i = 0;
            //     while (arr[i]){
            //         printf("str [%d] : %s\n", i, arr[i]);
            //         i++;
            //     }
            //     printf("------------------\n");
            //     current = current->next;
            // }
            
            expander(&data);
            dll_clear(data.lexer);
            data.lexer->head = NULL;
            data.lexer->tail = NULL;
            free(data.input);
            free(str);
        }
    }
	return 0;
}

///regler cat|ls ne separent oas en 2 cmd

//modifier le nom de la enum type