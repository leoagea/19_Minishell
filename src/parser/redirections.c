/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:40:47 by lagea             #+#    #+#             */
/*   Updated: 2024/08/01 17:59:47 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <stdio.h>

static void	delete_node(t_dll *cmd, t_node *delete)
{
	if (delete == cmd->head)
		dll_delete_head(cmd);
	else if (delete == cmd->tail)
		dll_delete_tail(cmd);
	else
		dll_delete_node(delete);
}

int	handle_redirections(t_dll *single_cmd, t_data *data)
{
	t_cmd	*cmd;
	t_node	*current;

	current = single_cmd->head;
	cmd = dll_cmd_new_node();
	dll_cmd_insert_tail(data->parser, cmd);
	cmd->redirections = dll_init();
	while (current != NULL)
	{
		if (current->type == 1 || current->type == 2 || current->type == 3
			|| current->type == 4)
		{
			cmd->num_redirections++;
			dll_insert_tail(ft_strdup(current->next->str), cmd->redirections);
			cmd->redirections->tail->type = current->type;
			delete_node(single_cmd, current);
			current = current->next;
			delete_node(single_cmd, current);
		}
		current = current->next;
	}
	return (0);
}
