/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:16:16 by lagea             #+#    #+#             */
/*   Updated: 2024/07/16 17:29:50 by lagea            ###   ########.fr       */
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
