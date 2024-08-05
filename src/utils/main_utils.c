/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:53:42 by vdarras           #+#    #+#             */
/*   Updated: 2024/08/02 17:17:05 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_arg(int argc, char **argv)
{
	if (argc != 1)
	{
		if (access(argv[1], F_OK) == 0)
		{
			printf("%s: %s: is a directory\n", argv[1], argv[1]);
			exit(126);
		}
		else
		{
			printf("bash: %s: no such file or directory\n", argv[1]);
			exit(127);
		}
	}
}

int	input_loop(char *line, t_data *data, t_cmd *command)
{
	data->input = readline("\001\e[0;31m\002> minishell$ \001\e[0m\002");
	if (data->input == NULL)
	{
		free_var("%lst", data->env);
		printf("\r\001\e[0;31m\002> minishell$ \001\e[0m\002exit\n");
		exit(0);
	}
	line = ft_strdup(data->input);
	free_str(data->input);
	data->input = line;
	if (data->input[0] != '\0')
	{
		if (data->input[0] != '\0')
			add_history(line);
		data->lexer = dll_init();
		if (lexer(line, data->lexer))
		{
			dll_clear(data->lexer);
			data->lexer->head = NULL;
			data->lexer->tail = NULL;
			return (1);
		}
		expand_exec(data, command);
	}
	return (free_str(data->input), 0);
}

void	expand_exec(t_data *data, t_cmd *command)
{
	expander(data);
	free_lexer(data->lexer);
	data->lexer->head = NULL;
	data->lexer->tail = NULL;
	data->parser = dll_cmd_init();
	parser(data);
	free_expander(data->expander);
	data->expander->head = NULL;
	data->expander->tail = NULL;
	command = data->parser->head;
	init_heredoc(data, command);
	exec_pipe(command, data);
	dll_cmd_clear(data->parser);
	data->parser->head = NULL;
	data->parser->tail = NULL;
	unlink_tmp();
}
