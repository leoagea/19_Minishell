/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:55 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 13:01:45 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	dll_clear(t_dll *dll)
{
	t_node	*temp;
	t_node	*current;

	if (!dll)
		return ;
	current = dll->head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	free(dll);
}
