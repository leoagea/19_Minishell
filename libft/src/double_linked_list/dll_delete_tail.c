/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_delete_tail.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:18:01 by lagea             #+#    #+#             */
/*   Updated: 2024/07/05 13:47:48 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	dll_delete_tail(t_dll *dll)
{
	t_node	*temp;

	temp = dll->tail;
	if (dll->head == dll->tail)
	{
		dll->head = NULL;
		dll->tail = NULL;
		free(temp);
	}
	else
	{
		dll->tail = temp->prev;
		dll->tail->next = NULL;
		free(temp);
	}
}
