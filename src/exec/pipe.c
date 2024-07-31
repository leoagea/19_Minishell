/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:43:00 by lagea             #+#    #+#             */
/*   Updated: 2024/07/31 20:50:37 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_path(t_data *data)
{
	t_env	*node;

	node = get_node(data->env, "PATH");
	if (!node)
		return (NULL);
	return (node->value);
}

char	*path(t_data *data, char *command)
{
	char	**dir_command;
	char	*temp;
	char	*final_path;
	int		i;
	char	*abs_path;

	abs_path = get_path(data);
	if (!abs_path)
		return (NULL);
	dir_command = ft_split(abs_path, ':');
	if (!dir_command)
		exit(1);
	i = -1;
	while (dir_command[++i])
	{
		temp = ft_strjoin("/", command);
		if (!temp)
			exit(1);
		final_path = ft_strjoin(dir_command[i], temp);
		if (!final_path)
			exit(1);
		free_str(temp);
		if (access(final_path, F_OK) == 0)
			return (free_arr(dir_command), final_path);
		free_str(final_path);
	}
	return (free_arr(dir_command), NULL);
}

void	absolute_path(t_data *data, t_cmd *command)
{
	t_cmd	*node;
	char	*path_str;

	node = command;
	while (node)
	{
		path_str = path(data, node->str[0]);
		if (access(node->str[0], F_OK) == -1)
		{
			if (path_str != NULL)
				node->absolute_path = path_str;
		}
		else
			node->absolute_path = ft_strdup(node->str[0]);
		node = node->next;
	}
}

char	**put_env_in_arr(t_lst *env)
{
	int		i;
	int		size;
	t_env	*node;
	char	**env_arr;

	i = 0;
	node = env->head;
	size = lst_size(env);
	env_arr = malloc(sizeof(char *) * size + 1);
	while (node)
	{
		env_arr[i] = ft_strdup(node->var);
		env_arr[i] = ft_strjoin(env_arr[i], "=");
		if (!node->value)
			env_arr[i] = ft_strjoin(env_arr[i], "");
		else
			env_arr[i] = ft_strjoin(env_arr[i], node->value);
		i++;
		node = node->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

void	exec_pipe(t_cmd *command, t_data *data)
{
	int		pipe_fd[2];
	int		fd_in;
	pid_t	pid;
	t_cmd	*node;
	int		child_count;
	pid_t	child_pids[2048];

	node = command;
	fd_in = STDIN_FILENO;
	is_builtin(node);
	if (node->next == NULL && node->is_builtin)
		return (exec_builtin(node, data), (void)0);
	if (!node->str[0])
		return ;
	child_count = 0;
	while (node)
	{
		absolute_path(data, node);
		if (node->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				exit(1);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit (1);
		}
		if (pid == 0)
		{
			if (fd_in != STDIN_FILENO)
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			redirections(node);
			if (node->next)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
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
		else
		{
			child_pids[child_count++] = pid;
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			if (node->next)
			{
				close(pipe_fd[1]);
				fd_in = pipe_fd[0];
			}
		}
		node = node->next;
	}
	wait_child(child_count, child_pids);
}
