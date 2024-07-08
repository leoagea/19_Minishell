/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:16:16 by lagea             #+#    #+#             */
/*   Updated: 2024/07/08 18:47:34 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_dll	*dll_init(void)
{
	t_dll	*stack;

	stack = malloc(sizeof(t_dll));
	if (!stack)
		return (NULL);
	stack->head = NULL;
	stack->tail = NULL;
	return (stack);
}

t_dll_cmd *dll_cmd_init(void)
{
    t_dll_cmd *dll;

    dll = malloc(sizeof(t_dll_cmd));
    if (!dll)
        return NULL;
    dll->head = NULL;
    dll->tail = NULL;
    return dll;
}

t_env_expand *env_var_init(void)
{
	t_env_expand *env;

	env = malloc(sizeof(t_env_expand));
	if (!env)
		return NULL;
	env->end = 0;
	env->start = 0;
	env->var = NULL;
	return env;
}

int		count_nodes(t_list *list)
{
	int	i;
	t_list	*node;

	i = 0;
	node = list;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

t_list	*init_env(char **envp)
{
	t_list	*env;
	t_list	*new_node;
	t_list	*node;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		new_node = ft_lstnew(envp[i]);
		if (!new_node)
			return (NULL); // free elements liste chainee
		ft_lstadd_back(&env, new_node);
		i++;
	}
	node = env;
	while (node != NULL)
	{
		node->flag = 0;
		node = node->next;
	}
	env->count = count_nodes(env);
	return (env);
}