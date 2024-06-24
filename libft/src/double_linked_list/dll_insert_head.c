/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_insert_head.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 13:18:21 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 15:46:01 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	dll_insert_head(int data, t_dll *dll)
{
	t_node	*new;

	new = dll_new_node(data);
	if (dll->head == NULL)
	{
		dll->head = new;
		dll->tail = new;
	}
	else
	{
		new->next = dll->head;
		dll->head->prev = new;
		dll->head = new;
	}
}
