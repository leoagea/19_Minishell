/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:01:17 by lagea             #+#    #+#             */
/*   Updated: 2024/07/16 17:23:16 by lagea            ###   ########.fr       */
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

	new_pwd = NULL;
	old_pwd = get_pwd();
	if (!str[1])
	{
		new_pwd = get_home(data);
		printf("new pwd : %s\n", new_pwd);
		if (!new_pwd)
		{
			ft_printf("bash: cd: HOME not set\n");
			return (1);
		}
	}
	else if (ft_strncmp("--", str[1], INT_MAX) == 0)
		new_pwd = get_home(data);
	else if (ft_strncmp("-", str[1], INT_MAX) == 0)
		new_pwd = get_old_pwd(data);
	else
		new_pwd = str[1];
	printf("old : %s\nnew : %s\n", old_pwd, new_pwd);
	change_directory(data, new_pwd, old_pwd);
	return (0);
}

int	cd(t_data *data)
{
	int	return_value;

	return_value = dispatch_cd(data, data->parser->head->str);
	return (return_value);
}
