/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:57:02 by lagea             #+#    #+#             */
/*   Updated: 2024/07/16 16:27:04 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_node_null(t_data *data)
{
	t_node	*current;

	current = data->expander->head;
	while (current != NULL)
	{
		if (current->str[0] == '\0')
			dll_delete_node(current);
		current = current->next;
	}
}
