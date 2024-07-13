/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/07/13 01:37:41 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_data	data;
	t_lst *env;
	// t_lst *export;
	t_cmd *command;
	
    (void) argc;
    (void) argv;
	g_exit_status = 1;
	printf("check \n");
	env = init_env(envp);
	printf("check 0\n");
	data.lexer = dll_init();
	data.env = env;
	data.parser = dll_cmd_init();
	// print_env(env);
	// print_export(data.env);
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
			// dll_print_forward(data.lexer);
			// printf("--------------------\n");
			expander(&data);
			// dll_print_forward(data.expander);
			parser(&data);

			dll_cmd_print_forward(data.parser);

			command = data.parser->head;
			command->env = envp;
			command->env_list = data.env;
			
			// dll_print_forward(data.expander);
			printf("===============================================\n");
			export(&data, data.parser->head);
			// print_env(data.env);
			// printf("===============================================\n");
			// print_export(data.env);
			// char **str;
			// str = data.parser->head->str;
			// int i = 0;
			// while (str[i])
			// {
			// 	printf("str [%d] : %s\n", i, str[i]);
			// 	i++;
			// }
		    // if (command->is_builtin == 0)
				 // 	execute_builtin(command);   // TODO
				 
			// exec_pipe(command);

			
			// char *test = get_pwd();
			// printf("pwd : %s\n", test);
			// pwd();
			// printf("exit code : %d\n", g_exit_status); 
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
