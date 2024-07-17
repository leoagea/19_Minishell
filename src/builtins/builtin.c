/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:21:10 by lagea             #+#    #+#             */
/*   Updated: 2024/07/17 17:11:45 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	is_builtin(t_cmd *command)
{
	t_cmd	*node;

	node = command;
	while (node)
	{
		if (ft_strncmp(node->str[0], "cd", INT_MAX) == 0
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
		export(data, command);
	else if (ft_strncmp(command->str[0], "unset", INT_MAX) == 0)
		unset(data, command);
	else if (ft_strncmp(command->str[0], "echo", INT_MAX) == 0)
		echo(command);
	else if (ft_strncmp(command->str[0], "env", INT_MAX) == 0)
		print_env(data->env);
	else if (ft_strncmp(command->str[0], "cd", INT_MAX) == 0)
		cd(data);
	else if ((ft_strncmp(command->str[0], "pwd", INT_MAX) == 0))
		pwd();
	else if ((ft_strncmp(command->str[0], "exit", INT_MAX) == 0))
		ft_exit(data, command);
	else
		return (-1);
	return (0);
}
