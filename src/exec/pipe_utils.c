/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:02:24 by vdarras           #+#    #+#             */
/*   Updated: 2024/08/01 20:23:37 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	wait_child(int child_count, pid_t *child_pids)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < child_count)
	{
		waitpid(child_pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			g_exit_status = WEXITSTATUS(wstatus);
		i++;
	}
}

void	exec_loop(t_data *data, t_cmd *node, t_exec *exec)
{
	absolute_path(data, node);
	if (node->next)
	{
		if (pipe(exec->pipe_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
	exec->pid = fork();
	if (exec->pid == -1)
	{
		perror("fork");
		exit (1);
	}
	if (exec->pid == 0)
		child_process(data, node, exec);
	else
		parent_process(node, exec);
}

void	child_process(t_data *data, t_cmd *node, t_exec *exec)
{
	if (exec->fd_in != STDIN_FILENO)
	{
		dup2(exec->fd_in, STDIN_FILENO);
		close(exec->fd_in);
	}
	redirections(node);
	if (node->next)
	{
		dup2(exec->pipe_fd[1], STDOUT_FILENO);
		close(exec->pipe_fd[1]);
		close(exec->pipe_fd[0]);
	}
	if (exec_builtin(node, data) == -1)
	{
		data->env_arr = put_env_in_arr(data->env);
		execve(node->absolute_path, node->str, data->env_arr);
		ft_putstr_fd("bash: ", 2);
		write(2, node->str[0], ft_strlen(node->str[0]));
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit (127);
	}
	else
		exit(0);
}

void	parent_process(t_cmd *node, t_exec *exec)
{
	exec->child_pids[exec->child_count++] = exec->pid;
	if (exec->fd_in != STDIN_FILENO)
		close(exec->fd_in);
	if (node->next)
	{
		close(exec->pipe_fd[1]);
		exec->fd_in = exec->pipe_fd[0];
	}
}
