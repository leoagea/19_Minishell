/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/07/09 16:10:17 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	EXIT_STATUS = 0;

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

// int main(void){
	
// 	char *input;
//     char *str;
//     char check;
//     t_data data;

//     data.lexer = dll_init();
//     data.parser = dll_cmd_init();
//     // Print a prompt and read a line of input from the user
//     while (1)
//     {
//         data.input = readline("minishell$ ");

//         // If the input is not NULL, print it and free the allocated memory
//         if (ft_strncmp(data.input, "\0", 1) == 0)
//             continue;
//         if (data.input) {
            
//             str = ft_strdup(data.input);
//             add_history(str);
            
//             lexer(str, data.lexer);
//             parser(&data);
//             dll_clear(data.lexer);
//             data.lexer->head = NULL;
//             data.lexer->tail = NULL;
//             free(data.input);
//             free(str);
//         }
//     }
// 	return 0;
// }

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_data	data;
	t_list *env;
	t_list *export;
	t_cmd *command;
	
	env = init_env(envp);
	export = init_export(env);
	data.lexer = dll_init();
	data.parser = dll_cmd_init();
	handle_signal();
	while (1)
	{
		data.input = readline("\001\e[0;31m\002> minishell$ \001\e[0m\002");
		if (data.input == NULL)
		{
			// write(1, "\33[2K\r", 6);
			// write(1, "\001\e[0;31m\002> minishell$ \001\e[0m\002exit\n", 33);
			write(1, "exit\n", 5);
			exit (0);
		}
		line = ft_strdup(data.input);
		if (data.input[0] != '\0')
		{
			if (data.input[0] != '\0')
				add_history(line);
			lexer(line, data.lexer);
			parser(&data);
			command = data.parser->head;
			command->env = envp;
			command->env_list = &env;
		    // if (command->is_builtin == 0)
				 // 	execute_builtin(command);   // TODO
			exec_pipe(command); 
			dll_clear(data.lexer);
			dll_cmd_clear(data.parser);
			data.parser->head = NULL;
			data.parser->tail = NULL;
			data.lexer->head = NULL;
			data.lexer->tail = NULL;
			// free_command(command); // TODO
		}
		free(line);
	}
	return (0);
}