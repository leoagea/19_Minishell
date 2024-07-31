/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:29:11 by lagea             #+#    #+#             */
/*   Updated: 2024/07/30 18:57:57 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_redirect(t_dll *redirec)
{
	t_node *tmp;
	t_node *node;

	if (!redirec)
		return ;
	node = redirec->head;
	while (node)
	{
		tmp = node;
		node = node->next;
		free_str(tmp->str);
		free(tmp);
		tmp = NULL;
	}
	free(redirec);
	redirec = NULL;
}

void	dll_cmd_clear(t_dll_cmd *dll)
{
	t_cmd	*temp;
	t_cmd	*current;

	if (!dll)
		return ;
	current = dll->head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free_arr(temp->str);
		free_redirect(temp->redirections);
		free(temp);
		temp = NULL;
	}
	free(dll);
	dll = NULL;
}

void	free_dll(t_dll *dll)
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
		// free_str(tmp->str);
		free(tmp);
		tmp = NULL;
	}
	free(dll);
	dll = NULL;
}

void	free_lexer(t_dll *dll)
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
		free_str(tmp->str);
		free(tmp);
		tmp = NULL;
	}
	free(dll);
	dll = NULL;
}

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
		// free_str(tmp->str);
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
		// free_arr(tmp->env);
		free_redirect(tmp->redirections);
		// free_lst(tmp->env_list);
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
