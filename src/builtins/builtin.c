/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:21:10 by lagea             #+#    #+#             */
/*   Updated: 2024/08/05 13:57:00 by vdarras          ###   ########.fr       */
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
	g_exit_status = 0;
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
}

void	exec_builtin_no_pipe(t_cmd *command, t_data *data)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		redirections(command);
		exec_builtin(command, data);
		exit(0);
	}
	wait(&wstatus);
	if (WEXITSTATUS(wstatus))
		g_exit_status = WEXITSTATUS(wstatus);
}

int	check_simple_builtin(t_cmd *node, t_data *data)
{
	if (node->next == NULL && node->is_builtin == true
		&& ft_strncmp(node->str[0], "exit", INT_MAX) != 0
		&& ft_strncmp(node->str[0], "export", INT_MAX) != 0
		&& ft_strncmp(node->str[0], "unset", INT_MAX) != 0
		&& ft_strncmp(node->str[0], "cd", INT_MAX) != 0)
	{
		exec_builtin_no_pipe(node, data);
		return (1);
	}
	else if (node->next == NULL && node->is_builtin == true
		&& ft_strncmp(node->str[0], "exit", INT_MAX) == 0)
		exec_builtin(node, data);
	else if (node->next == NULL && node->is_builtin == true
		&& ft_strncmp(node->str[0], "export", INT_MAX) == 0)
		exec_builtin(node, data);
	else if (node->next == NULL && node->is_builtin == true
		&& ft_strncmp(node->str[0], "unset", INT_MAX) == 0)
		exec_builtin(node, data);
	else if (node->next == NULL && node->is_builtin == true
		&& ft_strncmp(node->str[0], "cd", INT_MAX) == 0)
		exec_builtin(node, data);
	else
		return (0);
	return (2);
}
