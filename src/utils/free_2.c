/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:27:36 by lagea             #+#    #+#             */
/*   Updated: 2024/08/01 18:30:24 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_expander(t_dll *dll)
{
	t_node	*tmp;
	t_node	*node;

	if (!dll)
		return ;
	node = dll->head;
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp);
		tmp = NULL;
	}
	free(dll);
	dll = NULL;
}

void	free_cmd(t_dll_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*node;

	if (!cmd)
		return ;
	node = cmd->head;
	while (node)
	{
		tmp = node;
		node = node->next;
		free_arr(tmp->str);
		free_redirect(tmp->redirections);
		free(tmp);
		tmp = NULL;
	}
	free(cmd);
	cmd = NULL;
}

void	free_exp(t_env_expand *env)
{
	if (!env)
		return ;
	if (env->var)
	{
		free(env->var);
		env->var = NULL;
	}
	if (env->expand)
	{
		free(env->expand);
		env->expand = NULL;
	}
	free(env);
}
