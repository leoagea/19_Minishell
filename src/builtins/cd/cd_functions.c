/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:41:07 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 13:42:18 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	update_old(t_data *data, char *old)
{
	t_env	*node_old;
	t_env	*new_node;

	node_old = get_node(data->env, "OLDPWD");
	if (node_old)
	{
		free_str(node_old->value);
		node_old->value = ft_strdup(old);
		node_old->flag = 1;
	}
	else if (!node_old)
	{
		new_node = lst_new("OLDPWD", ft_strdup(old), 1);
		if (!new_node)
			return (1);
		lst_insert_tail(new_node, data->env);
	}
	return (0);
}

int	update_env(t_data *data, char *new, char *old)
{
	t_env	*node_pwd;
	t_env	*new_node;

	node_pwd = get_node(data->env, "PWD");
	if (!node_pwd)
	{
		new_node = lst_new("PWD", ft_strdup(new), 1);
		if (!new)
			return (1);
		lst_insert_tail(new_node, data->env);
	}
	else if (new && node_pwd)
	{
		free_str(node_pwd->value);
		node_pwd->value = ft_strdup(new);
	}
	if (update_old(data, old))
		return (1);
	return (0);
}

char	*get_accessible_pwd(char *pwd)
{
	char	*temp;
	char	*new;
	int		i;

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
	return (new);
}

static int	relative_path(char *new, char *old)
{
	char	*tmp;
	char	*new_join;

	tmp = ft_strjoin(old, "/");
	new_join = ft_strjoin(tmp, new);
	free_str(tmp);
	if (chdir(new) == -1)
	{
		if (access(new_join, F_OK) == -1 || access(new_join, X_OK) == -1)
			new_join = get_accessible_pwd(new_join);
		if (chdir(new_join) == -1)
			return (free_str(new_join), \
			ft_printf("bash: cd: %s: No such file or directory\n", new), 1);
		if (chdir(new) == -1)
			return (free_str(new_join), \
			ft_printf("bash: cd: %s: No such file or directory\n", new), 1);
	}
	free_str(new_join);
	return (0);
}

int	change_directory(t_data *data, char *new, char *old)
{
	int		return_value;
	char	*new_join;
	char	*upd_pwd;
	char	*tmp;

	if (!new)
		return (1);
	if (ft_strncmp("/Users/", new, 7) == 0)
	{
		if (access(new, F_OK) == -1 || access(new, X_OK) == -1)
			return (perror("cd"), 1);
		if (chdir(new) == -1)
			return (ft_printf("bash: cd: %s: No such file or directory\n", new),
				1);
	}
	else
	{
		if (relative_path(new, old))
			return (1);
	}
	upd_pwd = getcwd(NULL, 0);
	tmp = ft_strdup(upd_pwd);
	return_value = update_env(data, tmp, old);
	return (free_str(upd_pwd), free_str(old), free_str(tmp), 0);
}
