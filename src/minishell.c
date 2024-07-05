/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/07/05 17:50:44 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_dll	*dll_init(void)
{
	t_dll	*stack;

	stack = malloc(sizeof(t_dll));
	if (!stack)
		return (NULL);
	stack->head = NULL;
	stack->tail = NULL;
	return (stack);
}

t_dll_cmd *dll_cmd_init(void)
{
    t_dll_cmd *dll;

    dll = malloc(sizeof(t_dll_cmd));
    if (!dll)
        return NULL;
    dll->head = NULL;
    dll->tail = NULL;
    return dll;
}

int main(void)
{
	
	char *input;
    char *str;
    char check;
    t_data data;

    error_code = 0;
    data.lexer = dll_init();
    data.parser = dll_cmd_init();
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
