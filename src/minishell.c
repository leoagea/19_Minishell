/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/07/30 18:14:10 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int 	g_exit_status = 0;

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_data	data;
	t_cmd *command;
	
    (void) argc;
    (void) argv;
	data.env = init_env(envp);
	data.lexer = dll_init();
	data.parser = dll_cmd_init();
	if (init_shlvl(&data))
		return (1);
	handle_signal();
	while (1)
	{
		data.input = readline("\001\e[0;31m\002> minishell$ \001\e[0m\002");
		if (data.input == NULL)
		{
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
			{
				dll_clear(data.lexer);
				data.lexer->head = NULL;
				data.lexer->tail = NULL;
				continue ;
			}
			expander(&data);
			dll_clear(data.lexer);
			data.lexer->head = NULL;
			data.lexer->tail = NULL;

			parser(&data);
			dll_clear(data.expander);
			data.expander->head = NULL;
			data.expander->tail = NULL;

			command = data.parser->head;
			init_heredoc(command);
			exec_pipe(command, &data);
			dll_clear(data.lexer);
			dll_cmd_clear(data.parser);
			data.parser->head = NULL;
			data.parser->tail = NULL;
			unlink_tmp();
		}
		free(line);
	}
	return (0);
}
