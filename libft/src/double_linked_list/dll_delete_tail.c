/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_delete_tail.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 00:18:01 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 13:01:53 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

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
