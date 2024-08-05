/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:57:02 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 00:17:56 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_node_null(t_data *data)
{
	t_node	*current;

	current = data->expander->head;
	while (current != NULL)
	{
		if (current->str == NULL)
			dll_delete_node(current);
		current = current->next;
	}
}
