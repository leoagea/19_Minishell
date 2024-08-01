/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/07/31 20:54:09 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	t_cmd	*command;

	(void)argc;
	(void)argv;
	data.env = init_env(envp);
	if (init_shlvl(&data))
		return (1);
	handle_signal();
	while (1)
	{
		data.input = readline("\001\e[0;31m\002> minishell$ \001\e[0m\002");
		if (data.input == NULL)
		{
			free_var("%lst", data.env);
			printf("\r\001\e[0;31m\002> minishell$ \001\e[0m\002exit\n");
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
			expander(&data);
			free_lexer(data.lexer);
			data.lexer->head = NULL;
			data.lexer->tail = NULL;
			data.parser = dll_cmd_init();
			parser(&data);
			free_expander(data.expander);
			data.expander->head = NULL;
			data.expander->tail = NULL;
			command = data.parser->head;
			init_heredoc(command);
			exec_pipe(command, &data);
			dll_cmd_clear(data.parser);
			data.parser->head = NULL;
			data.parser->tail = NULL;
			unlink_tmp();
		}
		free_str(data.input);
	}
	return (0);
}
