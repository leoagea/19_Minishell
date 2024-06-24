/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_insert_tail.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:34:55 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 15:46:01 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	dll_insert_tail(int data, t_dll *dll)
{
	t_node	*new;

	new = dll_new_node(data);
	if (new == NULL)
	{
		dll_clear(dll);
		return ;
	}
	if (dll->tail == NULL)
	{
		dll->head = new;
		dll->tail = new;
	}
	else
	{
		new->prev = dll->tail;
		dll->tail->next = new;
		dll->tail = new;
	}
}
