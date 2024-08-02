/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:43:00 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 14:11:25 by lagea            ###   ########.fr       */
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
	t_cmd	*node;
	t_exec	exec;

	node = command;
	exec.fd_in = STDIN_FILENO;
	is_builtin(node);
	if (!node || !node->str[0] || node->str[0][0] == '\0')
		return ;
	if (check_simple_builtin(node, data))
		return ;
	exec.child_count = 0;
	while (node)
	{
		exec_loop(data, node, &exec);
		node = node->next;
	}
	wait_child(exec.child_count, exec.child_pids);
}
