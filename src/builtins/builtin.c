/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:21:10 by lagea             #+#    #+#             */
/*   Updated: 2024/07/31 16:22:28 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	is_builtin(t_cmd *command)
{
	t_cmd	*node;

	node = command;
	while (node)
	{
		if (!node->str[0])
			node->is_builtin = false;
		else if (ft_strncmp(node->str[0], "cd", INT_MAX) == 0
			|| ft_strncmp(node->str[0], "echo", INT_MAX) == 0
			|| ft_strncmp(node->str[0], "env", INT_MAX) == 0
			|| ft_strncmp(node->str[0], "exit", INT_MAX) == 0
			|| ft_strncmp(node->str[0], "export", INT_MAX) == 0
			|| ft_strncmp(node->str[0], "pwd", INT_MAX) == 0
			|| ft_strncmp(node->str[0], "unset", INT_MAX) == 0)
			node->is_builtin = true;
		else
			node->is_builtin = false;
		node = node->next;
	}
}

int	exec_builtin(t_cmd *command, t_data *data)
{
	if (ft_strncmp(command->str[0], "export", INT_MAX) == 0)
		return (_export(data, command), 0);
	else if (ft_strncmp(command->str[0], "unset", INT_MAX) == 0)
		return (unset(data, command), 0);
	else if (ft_strncmp(command->str[0], "echo", INT_MAX) == 0)
		return (echo(command), 0);
	else if (ft_strncmp(command->str[0], "env", INT_MAX) == 0)
		return (print_env(data->env), 0);
	else if (ft_strncmp(command->str[0], "cd", INT_MAX) == 0)
		return (cd(data), 0);
	else if ((ft_strncmp(command->str[0], "pwd", INT_MAX) == 0))
		return (pwd(), 0);
	else if ((ft_strncmp(command->str[0], "exit", INT_MAX) == 0))
		return (__exit(data, command), 0);
	else
		return (-1);
	g_exit_status = 0;
	return (0);
}
