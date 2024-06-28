/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/06/28 21:26:53 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(void){
	
	char *input;
    char *str;
	t_tokens token;
	
    // Print a prompt and read a line of input from the user
    while (1)
    {
        input = readline("minishell$ ");

        // If the input is not NULL, print it and free the allocated memory
        if (input) {
            
            str = ft_strdup(input);
            add_history(str);
            
            lexer(str, &token);

            free(input);
            free(str);
        }
    }
	return 0;
}