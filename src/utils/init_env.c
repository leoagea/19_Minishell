/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:04:43 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 13:11:12 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_value(t_env *env, char *str, int i)
{
	int		start;
	char	*tmp;

	start = i + 1;
	while (str[i])
		i++;
	tmp = ft_substr(str, start, i - start);
	if (!tmp)
		return (1);
	env->value = ft_strdup(tmp);
	free_str(tmp);
	return (0);
}

t_env	*get_env_var(char *envp)
{
	int		i;
	int		start;
	char	*str;
	char	*tmp;
	t_env	*env;

	env = lst_new(NULL, NULL, 1);
	if (!env)
		return (NULL);
	str = envp;
	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	tmp = ft_substr(str, 0, i);
	env->var = ft_strdup(tmp);
	free_str(tmp);
	if (ft_strncmp(env->var, "OLDPWD", INT_MAX) == 0)
	{
		env->flag = 0;
		return (env);
	}
	get_value(env, str, i);
	return (env);
}

static int	insert_node_env_i(t_lst *env, char *pwd)
{
	t_env	*node;

	node = lst_new(ft_strdup("PWD"), pwd, 1);
	if (!node)
		return (1);
	lst_insert_tail(node, env);
	node = lst_new(ft_strdup("SHLVL"), ft_strdup("1"), 1);
	if (!node)
		return (1);
	lst_insert_tail(node, env);
	node = lst_new(ft_strdup("_"), ft_strjoin(pwd, "/./minishell"), 1);
	if (!node)
		return (1);
	lst_insert_tail(node, env);
	node = lst_new(ft_strdup("OLDPWD"), NULL, 0);
	if (!node)
		return (1);
	lst_insert_tail(node, env);
	node = lst_new(ft_strdup("PATH"), ft_strjoin(PATH, PATH2), 2);
	if (!node)
		return (1);
	lst_insert_tail(node, env);
	return (0);
}

t_lst	*init_env_i(void)
{
	char	*pwd;
	t_lst	*env;

	env = lst_init();
	if (!env)
		return (NULL);
	pwd = get_pwd();
	if (!pwd)
		return (NULL);
	if (insert_node_env_i(env, pwd))
		return (NULL);
	return (env);
}

t_lst	*init_env(char **envp)
{
	t_lst	*env;
	t_env	*new_node;
	t_env	*env_var;
	int		i;

	i = 0;
	if (!envp || !*envp)
		return (init_env_i());
	env = lst_init();
	if (!env)
		return (NULL);
	while (envp[i])
	{
		env_var = get_env_var(envp[i]);
		new_node = lst_new(env_var->var, env_var->value, env_var->flag);
		free(env_var);
		env_var = NULL;
		if (!new_node)
			return (NULL);
		lst_insert_tail(new_node, env);
		i++;
	}
	return (env);
}
