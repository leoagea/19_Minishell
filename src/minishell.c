/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/07/18 17:28:01 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_data	data;
	// t_lst *export;
	t_cmd *command;
	
    (void) argc;
    (void) argv;
	g_exit_status = 1;
	data.env = init_env(envp);
	data.lexer = dll_init();
	data.parser = dll_cmd_init();
	// print_env(env);
	printf("Start\n");
	// print_export(data.env);
	if (init_shlvl(&data))
		return 1;
	handle_signal();
	while (1)
	{
		data.input = readline("\001\e[0;31m\002> minishell$ \001\e[0m\002");
		if (data.input == NULL)
		{
			// write(1, "\33[2K\r", 6);
			// write(1, "\001\e[0;31m\002> minishell$ \001\e[0m\002exit\n", 33);
			free_var("%dll %dll %cmd %lst %exp", data.lexer, data.expander, data.parser, data.env, data.env_expand);
			write(1, "exit\n", 5);
			exit (0);
		}
		line = ft_strdup(data.input);
		free(data.input);
		if (data.input[0] != '\0')
		{
			if (data.input[0] != '\0')
				add_history(line);
			if (lexer(line, data.lexer))
				continue ;
			printf("test \n");
			// dll_print_forward(data.lexer);
			// printf("--------------------\n");
			expander(&data);
			printf("test 1\n");
			// dll_print_forward(data.expander);
			parser(&data);

			// dll_cmd_print_forward(data.parser);

			command = data.parser->head;
			command->env = envp;
			command->env_list = data.env;
			
			// dll_print_forward(data.expander);
			// printf("===============================================\n");
			// if (ft_strncmp(data.parser->head->str[0], "export", INT_MAX) == 0)
			// 	export(&data, data.parser->head);
			// else if (ft_strncmp(data.parser->head->str[0], "unset", INT_MAX) == 0)
			// 	unset(&data, data.parser->head);
			// else if (ft_strncmp(data.parser->head->str[0], "env", INT_MAX) == 0)
			// 	print_env(data.env);
			// else if (ft_strncmp(data.parser->head->str[0], "cd", INT_MAX) == 0)
			// 	cd(&data);
			// else if ((ft_strncmp(data.parser->head->str[0], "pwd", INT_MAX) == 0))
			// 	pwd();
			// else if (ft_strncmp(command->str[0], "echo", INT_MAX) == 0)
			// 	return echo(data.parser->head);
		    // if (command->is_builtin == 0)
				 // 	execute_builtin(command);   // TODO
				 
			exec_pipe(command, &data);

			// char *test = get_pwd();
			// printf("pwd : %s\n", test);
			// pwd();
			// printf("exit code : %d\n", g_exit_status); 
			dll_clear(data.lexer);
			dll_clear(data.expander);
			dll_cmd_clear(data.parser);
			data.lexer->head = NULL;
			data.lexer->tail = NULL;
			data.parser->head = NULL;
			data.parser->tail = NULL;
			data.expander->head = NULL;
			data.expander->tail = NULL;
			// free_command(command); // TODO
		}
		// free_var("%str %dll %dll  ")
		free(line);
	}
	return (0);
}

//verifie si il y a des nodes parser avant de rentrer dans l exec

//check pwd si dans le dir minishell