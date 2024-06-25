/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/06/25 18:31:23 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(void){
	
	char *input;
	t_tokens token;
	
    // Print a prompt and read a line of input from the user
    input = readline("minishell$ ");

    // If the input is not NULL, print it and free the allocated memory
    if (input) {
        // printf("You entered: %s\n", input);
		// token_read(input, &token);
        // int j = quote_border(input, 0, '"');
        // printf("j : %d\n", j);
        test_2(input, &token);
        free(input);
    }
	return 0;
}