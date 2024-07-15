/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:41:07 by lagea             #+#    #+#             */
/*   Updated: 2024/07/15 17:22:45 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int update_env(t_data *data, char *new, char *old)
{
	t_env *node_pwd;
	t_env *node_old;
	t_env *new_node;
	
	node_pwd = get_node(data->env, "PWD");
	node_pwd->value = new;
	node_old = get_node(data->env, "OLDPWD");
	if(!node_old->value)
	{
		node_old->value = old;
		node_old->flag = 1;
	}
	else if (!node_old)
	{
		new_node = lst_new("OLDPWD", old, 1);
		if (!new)
			return 1;
		lst_insert_tail(new_node, data->env);
	}
	return 0;
}


int change_directory(t_data *data, char *new, char *old)
{
	int return_value;
	
	if (!new)
		return 1;
	if (access(new, F_OK) && access(new, X_OK) == -1)
	{
		perror("cd");
		return 1;
	}
	chdir(new);
	return_value = update_env(data, new, old);
	printf("check \n");
	return 0;	
}
