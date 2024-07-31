/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:04:43 by lagea             #+#    #+#             */
/*   Updated: 2024/07/31 15:13:39 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*get_env_var(char *envp)
{
	int		i;
	int		start;
	char	*str;
	char *tmp;
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
	start = i + 1;
	while (str[i++])
		;
	tmp = ft_substr(str, start, i - start);
	env->value = ft_strdup(tmp);
	free_str(tmp);
	return (env);
}

t_lst	*init_env_i(void)
{
	char	*pwd;
	t_env	*node;
	t_lst	*env;

	env = lst_init();
	if (!env)
		return (NULL);
	pwd = get_pwd();
	if (!pwd)
		return (NULL);
	node = lst_new(ft_strdup("PWD"), pwd, 1);
	if (!node)
		return (NULL);
	lst_insert_tail(node, env);
	node = lst_new(ft_strdup("SHLVL"), ft_strdup("1"), 1);
	if (!node)
		return (NULL);
	lst_insert_tail(node, env);
	node = lst_new(ft_strdup("_"), ft_strjoin(pwd, "/./minishell"), 1);
	if (!node)
		return (NULL);
	lst_insert_tail(node, env);
	return (env);
}

t_lst	*init_env(char **envp)
{
	t_lst	*env;
	t_env	*new_node;
	t_env	*env_var;
	int		i;

	i = 0;
	env = lst_init();
	if (!envp || !*envp)
	{
		env = init_env_i();
		return (env);
	}
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
