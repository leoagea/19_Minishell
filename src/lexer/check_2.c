/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:35:53 by lagea             #+#    #+#             */
/*   Updated: 2024/08/01 17:55:27 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_inside_pipe(t_dll *tokens)
{
	t_node	*current;

	current = tokens->head;
	while (current)
	{
		if (current->type == PIPE && current->next->type == PIPE)
			return (1);
		current = current->next;
	}
	return (0);
}
