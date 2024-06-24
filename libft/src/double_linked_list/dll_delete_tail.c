/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_delete_tail.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:18:01 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 15:46:01 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	dll_delete_tail(t_dll *dll)
{
	t_node	*temp;

	temp = dll->tail;
	if (dll->head == dll->tail)
		return ;
	dll->tail = temp->prev;
	dll->tail->next = NULL;
	free(temp);
}
