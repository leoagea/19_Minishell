/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/07/02 16:32:33 by lagea            ###   ########.fr       */
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
	t_dll   *tokens;

    tokens = dll_init();
    // Print a prompt and read a line of input from the user
    while (1)
    {
        input = readline("minishell$ ");

        // If the input is not NULL, print it and free the allocated memory
        if (input) {
            
            str = ft_strdup(input);
            add_history(str);
            
            lexer(str, tokens);
            dll_clear(tokens);
            tokens->head = NULL;
            tokens->tail = NULL;
            free(input);
            free(str);
        }
    }
	return 0;
}