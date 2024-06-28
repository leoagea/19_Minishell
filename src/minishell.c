/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/06/28 17:00:43 by lagea            ###   ########.fr       */
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
            // printf("You entered: %s\n", input);
            str = ft_strdup(input);
            add_history(str);
            // printf("%d\n", check_whitespace(str, 0));
            // printf("old str : '%s'\n",str);
            
            // int i = 0;
            // while (check_whitespace(str, i))
            //     i++;
            // char *skip = ft_substr(str, 0 , i);
            // str = ft_strtrim(str, skip);

            // printf("new str : '%s'\n",str);
            
            lexer(str, &token);
            
            // int j = quote_border(input, 0, '"');
            // printf("j : %d\n", j);
            free(input);
            // if (str){
            free(str);
            //     str = NULL;   
            // }
        }
    }
	return 0;
}