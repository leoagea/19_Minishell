/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:16:16 by lagea             #+#    #+#             */
/*   Updated: 2024/08/01 18:26:54 by lagea            ###   ########.fr       */
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

t_dll_cmd	*dll_cmd_init(void)
{
	t_dll_cmd	*dll;

	dll = malloc(sizeof(t_dll_cmd));
	if (!dll)
		return (NULL);
	dll->head = NULL;
	dll->tail = NULL;
	return (dll);
}

t_env_expand	*env_var_init(void)
{
	t_env_expand	*env;

	env = malloc(sizeof(t_env_expand));
	if (!env)
		return (NULL);
	env->end = 0;
	env->sub = 0;
	env->start = 0;
	env->var_len = 0;
	env->var = NULL;
	env->expand = NULL;
	return (env);
}

t_lst	*lst_init(void)
{
	t_lst	*env;

	env = malloc(sizeof(t_lst));
	if (!env)
		return (NULL);
	env->head = NULL;
	env->tail = NULL;
	return (env);
}

int	init_shlvl(t_data *data)
{
	int		sh_lvl;
	t_env	*new;
	t_env	*node;

	node = get_node(data->env, "SHLVL");
	if (!node)
	{
		new = lst_new("SHLVL", ft_itoa(2), 1);
		if (!new)
			return (1);
		lst_insert_tail(new, data->env);
	}
	else
	{
		sh_lvl = ft_atoi(node->value);
		if (sh_lvl >= 999)
			node->value = ft_strdup("");
		else if (sh_lvl < 0)
			node->value = ft_strdup("0");
		node->value = ft_itoa(sh_lvl + 1);
	}
	return (0);
}
