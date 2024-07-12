/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:04:43 by lagea             #+#    #+#             */
/*   Updated: 2024/07/12 14:27:03 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env *get_env_var(char *envp)
{
    int i;
    int start;
    char *str;
    t_env *env;
    
    env = malloc(sizeof(t_env));
    if (!env)
        return NULL;
    env->flag = 1;
    env->var = NULL;
    env->value = NULL;
    str = envp;
    i = 0;
    while(str[i] != '=' && str[i])
        i++;
    env->var = ft_substr(str, 0, i);
    if (ft_strncmp(env->var, "OLDPWD", INT_MAX) == 0)
    {
        env->flag = 0;
        return env;
    }
    start = i + 1;
    while (str[i++]);
    env->value = ft_substr(str, start, i - start);
    return env;
}

static t_env	*lstnew(char *var, char *value, int flag)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = var;
	new->value = value;
	new->flag = flag;
	new->next = NULL;
	return (new);
}

static void	lst_insert_tail(t_env *new, t_lst *lst)
{
	if (lst->tail == NULL)
	{
		lst->head = new;
		lst->tail = new;
	}
	else
	{
		lst->tail->next = new;
		lst->tail = new;
	}
}

t_lst	*init_env(char **envp)
{
    t_lst *env;
	t_env	*new_node;
    t_env *env_var;
	int		i;

	i = 0;
    env = lst_init();
	while (envp[i])
	{
        // printf("%d\n", i);
        env_var = get_env_var(envp[i]);
        // printf("%s=%s   falg : %d\n", env_var->var, env_var->value, env_var->flag);
		new_node = lstnew(env_var->var, env_var->value, env_var->flag);
		if (!new_node)
			return (NULL); // free elements liste chainee
		lst_insert_tail(new_node, env);
        // printf("%s=%s   falg : %d\n", env->tail->var, env->tail->value, env->tail->flag);
        // printf("%s=%s   falg : %d\n", env->tail->var, env->tail->value, env->tail->flag);
		i++;
	}
    print_env(env);
    // print_env(env);
    // print_env(env);
    // print_env(env);
	return (env);
}
