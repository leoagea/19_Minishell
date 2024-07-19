/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:41:07 by lagea             #+#    #+#             */
/*   Updated: 2024/07/19 17:59:42 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	update_env(t_data *data, char *new, char *old)
{
	t_env	*node_pwd;
	t_env	*node_old;
	t_env	*new_node;

	node_pwd = get_node(data->env, "PWD");
	if (new)
		node_pwd->value = new;
	else
		node_pwd->value = ft_strdup("");
	node_old = get_node(data->env, "OLDPWD");
	if (!node_old->value)
	{
		node_old->value = old;
		node_old->flag = 1;
	}
	else if (!node_old)
	{
		new_node = lst_new("OLDPWD", old, 1);
		if (!new)
			return (1);
		lst_insert_tail(new_node, data->env);
	}
	return (0);
}

int	change_directory(t_data *data, char *new, char *old)
{
	char *pwd;
	int	return_value;
	
	// printf("check 3\n");
	if (!new)
		return (1);
	// printf("check 4\n");
	if (access(new, F_OK) && access(new, X_OK) == -1)
	{
		perror("cd");
		return (1);
	}
	// printf("check 5\n");
	if (chdir(new) == -1)
	{
		ft_printf("bash: cd: %s: No such file or directory");
		return (1);
	}
	// printf("check 6\n");
	return_value = update_env(data, getcwd(pwd, 10000), old);
	// printf("check 7\n");
	return (0);
}

// char *get_accessible_pwd(t_data * data)
// {
// 	char *new;
// 	char *pwd;
	
// }
