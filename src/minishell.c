/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/07/30 17:45:01 by lagea            ###   ########.fr       */
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
	// data.lexer = dll_init();
	// data.parser = dll_cmd_init();
	// print_env(env);
	// printf("Start\n");
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
			// free_var("%dll %dll %cmd %lst", data.lexer, data.expander, data.parser, data.env);
			free_var("%lst", data.env);
			write(1, "exit\n", 5);
			// system("leaks minishell");
			exit (0);
		}
		line = ft_strdup(data.input);
		free_str(data.input);
		data.input = line;
		if (data.input[0] != '\0')
		{
			if (data.input[0] != '\0')
				add_history(line);
			data.lexer = dll_init();			
			if (lexer(line, data.lexer))
			{
				dll_clear(data.lexer);
				data.lexer->head = NULL;
				data.lexer->tail = NULL;
				continue ;
			}
			// printf("test \n");
			// dll_print_forward(data.lexer);
			// printf("--------------------\n");
			expander(&data);
			// dll_clear(data.lexer);
			free_lexer(data.lexer);
			// free(data.lexer);
			data.lexer->head = NULL;
			data.lexer->tail = NULL;
			// dll_print_forward(data.expander);
			// printf("test 1\n");
			data.parser = dll_cmd_init();
			parser(&data);
			free_expander(data.expander);
			// free(data.expander);
			data.expander->head = NULL;
			data.expander->tail = NULL;

			// dll_cmd_print_forward(data.parser);

			command = data.parser->head;
			init_heredoc(command);
			exec_pipe(command, &data);
			// printf("exit code : %d\n", g_exit_status); 
			dll_cmd_clear(data.parser);
			// free(data.parser);
			data.parser->head = NULL;
			data.parser->tail = NULL;
			// free_command(command); // TODO
		}
		// free_var("%str %dll %dll  ")
		free_str(data.input);
	}
	return (0);
}

//segfault when exit and ctrl D needed to be fixed