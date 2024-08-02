/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:18:44 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 12:33:37 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	heredoc_token(t_data *data, t_node *current, char *str)
{
	dll_insert_tail(ft_strdup(str), data->expander);
	data->expander->tail->type = current->type;
	current = current->next;
	str = expand_heredoc(current->str);
	dll_insert_tail(ft_strdup(str), data->expander);
	data->expander->tail->type = current->type;
}

static void	other_token(t_data *data, t_node *current)
{
	dll_insert_tail(ft_strdup(current->str), data->expander);
	data->expander->tail->type = current->type;
}

static void	word(t_data *data, t_node *current, char *str)
{
	char	*cpy;

	cpy = sweep_word(data, str);
	if (!cpy)
		return ;
	dll_insert_tail(ft_strdup(cpy), data->expander);
	free_str(cpy);
	data->expander->tail->type = current->type;
}

static void	dispatch_expand(t_data *data)
{
	char	*str;
	t_node	*current;

	current = data->lexer->head;
	while (current != NULL)
	{
		str = current->str;
		if (current->type != PIPE && current->type != INPUT
			&& current->type != TRUNC && current->type != APPEND
			&& current->type != HEREDOC)
			word(data, current, str);
		else if (current->type == HEREDOC)
		{
			heredoc_token(data, current, str);
			current = current->next;
		}
		else
			other_token(data, current);
		current = current->next;
	}
}

int	expander(t_data *data)
{
	char	*cpy;

	data->expander = dll_init();
	if (!data->expander)
		return (1);
	data->env_expand = env_var_init();
	if (!data->env_expand)
		return (1);
	dispatch_expand(data);
	check_node_null(data);
	free(data->env_expand);
	data->env_expand = NULL;
	return (0);
}
