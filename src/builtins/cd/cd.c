/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:01:17 by lagea             #+#    #+#             */
/*   Updated: 2024/07/30 15:43:51 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static char	*get_home(t_data *data)
{
	int		slash;
	char	*pwd;
	t_env	*node;

	node = data->env->head;
	while (node != NULL && ft_strncmp(node->var, "HOME", INT_MAX) != 0)
		node = node->next;
	if (!node || !node->value)
		return (NULL);
	slash = 0;
	return (node->value);
}

static char	*get_old_pwd(t_data *data)
{
	char	*new_pwd;
	t_env	*node_old;

	node_old = get_node(data->env, "OLDPWD");
	if (!node_old->value)
	{
		ft_printf("bash: cd: OLDPWD not set\n");
		return (NULL);
	}
	new_pwd = node_old->value;
	return (new_pwd);
}

static int	dispatch_cd(t_data *data, char **str)
{
	char	*new_pwd;
	char	*old_pwd;
	t_env	*env_pwd;

	new_pwd = NULL;
	// printf("check 1\n");
	env_pwd = get_node(data->env, "PWD");
	if (!env_pwd)
		old_pwd = get_pwd();
	else
		old_pwd = env_pwd->value;
	// if (!old_pwd)
	// 	return (perror("getcwd"), 1);
	// printf("check 2\n");
	if (!str[1])
	{
		new_pwd = get_home(data);
		// printf("new pwd : %s\n", new_pwd);
		if (!new_pwd)
			return (ft_printf("bash: cd: HOME not set\n"), 1);
	}
	else if (ft_strncmp("--", str[1], INT_MAX) == 0)
		new_pwd = get_home(data);
	else if (ft_strncmp("-", str[1], INT_MAX) == 0)
		new_pwd = get_old_pwd(data);
	// else if (ft_strncmp("..", str[1], 2) == 0)
	// 	new_pwd = get_accessible_pwd(data);
	else
		new_pwd = str[1];
	// printf("old : %s\nnew : %s\n", old_pwd, new_pwd);
	g_exit_status = change_directory(data, new_pwd, old_pwd);
	return (0);
}

int	cd(t_data *data)
{
	int	return_value;

	return_value = dispatch_cd(data, data->parser->head->str);
	return (return_value);
}
