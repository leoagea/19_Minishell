/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 23:04:43 by lagea             #+#    #+#             */
/*   Updated: 2024/07/12 00:35:50 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_get_env *get_env_var(char *envp)
{
    int i;
    int start;
    char *str;
    t_get_env *env;
    
    env = malloc(sizeof(t_get_env));
    if (!env)
        return NULL;
    env->var = NULL;
    env->value = NULL;
    str = envp;
    while(str[i] != '=' && str[i])
        i++;
    env->var = ft_substr(str, 0, i);
    start = i + 1;
    while (str[i])
        i++;
    env->value = ft_substr(str, start, i - start);
    return env;
}

t_list	*init_env(char **envp)
{
	t_list	*env;
	t_list	*new_node;
	t_list	*node;
    t_get_env *env_var;
	int		i;

	i = 0;
	// env = NULL;
	while (envp[i])
	{
        // printf("%d\n", i);
        env_var = get_env_var(envp[i]);
        // printf("var : '%s', value : '%s'\n", env_var->var, env_var->value);
		new_node = ft_lstnew(env_var->var, env_var->value, 1);
		if (!new_node)
			return (NULL); // free elements liste chainee
		ft_lstadd_back(&env, new_node);
		i++;
	}
	node = ft_lstlast(env);
	node->next = NULL;
	return (env);
}
