/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:41:07 by lagea             #+#    #+#             */
/*   Updated: 2024/07/30 16:39:32 by lagea            ###   ########.fr       */
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

static int is_absolute(char *new)
{
	if (ft_strncmp("/Users/", new, 7) == 0)
		return 1;
	return 0;
}

char *get_accessible_pwd(char *pwd)
{
	char *temp;
	char *new;
	int i;
	
	new = "/";
	temp = ft_substr(pwd, 0, 1);
	pwd = ft_substr(pwd, 1, ft_strlen(pwd) - 1);
	while (!access(new, F_OK) && !access(new, X_OK))
	{
		i = 0;
		while (pwd[i + 1] && pwd[i + 1] != '/')
			i++;
		temp = ft_substr(pwd, 0, i + 1);
		pwd = ft_substr(pwd, i + 1, ft_strlen(pwd) - i - 1);
		new = ft_strjoin(new, temp);
	}
	new = ft_substr(new, 0, ft_strlen(new) - ft_strlen(temp));
	return new;
}

int	change_directory(t_data *data, char *new, char *old)
{
	int	return_value;
	char *new_join;
	char *upd_pwd;
	char *tmp;
	// printf("check 3\n"); 
	if (!new)
		return (1);
	// printf("check 4\n");
	if (is_absolute(new))
	{
		if (access(new, F_OK) == -1 || access(new, X_OK) == -1)
			return (perror("cd"), 1);
		// printf("check abs\n");
		// printf("chdir(%s)\n", new);
		if (chdir(new) == -1)
			return (ft_printf("bash: cd: %s: No such file or directory\n", new), 1);
	}
	else 
	{
		tmp = ft_strjoin(old, "/");
		new_join = ft_strjoin(tmp, new);
		free_str(tmp);
		if (chdir(new) == -1)
			return (ft_printf("bash: cd: %s: No such file or directory\n", new), 1);
		if (access(new_join, F_OK) == -1 || access(new_join, X_OK) == -1)
			new_join = get_accessible_pwd(new_join);
		// printf("check non abs\n");
		// printf("chdir(%s)\n", new);
		if (chdir(new_join) == -1)
			return (free_str(new_join),ft_printf("bash: cd: %s: No such file or directory\n", new), 1);
		free_str(new_join);
	}
	// printf("check 6\n");
	// free_str(new_join);
	upd_pwd = getcwd(NULL, 0);
	tmp = ft_strdup(upd_pwd);
	return_value = update_env(data, tmp, old);
	return (free_str(upd_pwd), free_str(tmp), 0);
}

