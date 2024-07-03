/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/07/03 18:18:48 by lagea            ###   ########.fr       */
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

int main(void){
	
	char *input;
    char *str;
    char check;
    t_data data;

    data.lexer = dll_init();
    // Print a prompt and read a line of input from the user
    while (1)
    {
        data.input = readline("minishell$ ");

        // If the input is not NULL, print it and free the allocated memory
        if (data.input) {
            
            str = ft_strdup(data.input);
            add_history(str);
            
            lexer(str, data.lexer);
            parser(&data);
            dll_clear(data.lexer);
            data.lexer->head = NULL;
            data.lexer->tail = NULL;
            free(data.input);
            free(str);
        }
    }
	return 0;
}