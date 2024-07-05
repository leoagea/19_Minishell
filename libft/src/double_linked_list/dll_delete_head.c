/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_delete_head.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:18:01 by lagea             #+#    #+#             */
/*   Updated: 2024/07/05 13:45:56 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	dll_delete_head(t_dll *dll)
{
	t_node	*temp;

	temp = dll->head;
	if (dll->head == dll->tail)
	{
		dll->head = NULL;
		dll->tail = NULL;
		free(temp);
	}
	else
	{
		dll->head = temp->next;
		dll->head->prev = NULL;
		free(temp);
	}
}
