/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:18:44 by lagea             #+#    #+#             */
/*   Updated: 2024/07/22 15:31:10 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	heredoc_token(t_data *data, t_node *current, char *cpy)
{
	dll_insert_tail(cpy, data->expander);
	data->expander->tail->type = current->type;
	current = current->next;
	cpy = expand_heredoc(current->str);
	dll_insert_tail(cpy, data->expander);
	data->expander->tail->type = current->type;
}

static void	other_token(t_data *data, t_node *current)
{
	dll_insert_tail(current->str, data->expander);
	data->expander->tail->type = current->type;
}

static void	word(t_data *data, t_node *current, char *cpy, char *str)
{
	cpy = sweep_word(data, str);
	if (!cpy || cpy[0] == '\0')
		return ;
	dll_insert_tail(cpy, data->expander);
	data->expander->tail->type = current->type;
}

int	expander(t_data *data)
{
	char	*str;
	char	*cpy;
	t_node	*current;

	data->expander = dll_init();
	data->env_expand = env_var_init();
	current = data->lexer->head;
	while (current != NULL)
	{
		str = current->str;
		if (current->type != PIPE && current->type != INPUT
			&& current->type != TRUNC && current->type != APPEND
			&& current->type != HEREDOC)
			word(data, current, cpy, str);
		else if (current->type == HEREDOC)
			heredoc_token(data, current, cpy);
		else
			other_token(data, current);
		current = current->next;
	}
	check_node_null(data);
	return (0);
}
