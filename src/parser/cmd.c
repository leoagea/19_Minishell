/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:12:31 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 17:18:36 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_dll	*isolate_single_cmd(t_node *start)
{
	t_node	*current;
	t_node	*currend_cmd;
	t_dll	*single_cmd;

	single_cmd = dll_init();
	current = start;
	while (current != NULL)
	{
		if (current->type == PIPE)
			return (single_cmd);
		dll_insert_tail(current->str, single_cmd);
		currend_cmd = single_cmd->tail;
		currend_cmd->type = current->type;
		current = current->next;
	}
	return (single_cmd);
}

static int	check_return_cond(t_data *data, t_dll *cmd)
{
	if (dll_size(cmd) == 0)
	{
		data->parser->tail->str[0] = NULL;
		return (1);
	}
	if (ft_strncmp(cmd->tail->str, cmd->head->str, INT_MAX) == 0
		&& cmd->tail->str[0] == '\0')
	{
		data->parser->tail->str[0] = NULL;
		return (1);
	}
	return (0);
}

static int	put_in_str(t_data *data, t_dll *cmd)
{
	int		i;
	int		nb_tokens;
	t_node	*current;

	i = 0;
	current = cmd->head;
	nb_tokens = dll_size(cmd);
	data->parser->tail->str = malloc(sizeof(char *) * nb_tokens + 1);
	if (check_return_cond(data, cmd))
		return (0);
	while (current->str && current->str[0] == '\0')
		current = current->next;
	while (current != NULL)
	{
		if (current == NULL)
			break ;
		data->parser->tail->str[i] = current->str;
		data->parser->tail->str[i][ft_strlen(current->str)] = '\0';
		current = current->next;
		i++;
	}
	data->parser->tail->str[i] = NULL;
	return (0);
}

int	parser(t_data *data)
{
	t_node	*current;
	t_dll	*single_cmd;
	int		i;

	i = 1;
	current = data->expander->head;
	while (current != NULL)
	{
		single_cmd = isolate_single_cmd(current);
		handle_redirections(single_cmd, data);
		while (current != NULL && current->type != PIPE)
		{
			current = current->next;
		}
		if (current != NULL && current->type == PIPE)
			current = current->next;
		put_in_str(data, single_cmd);
		data->parser->tail->num_cmd = i;
		i++;
		free_dll(single_cmd);
	}
	return (0);
}
