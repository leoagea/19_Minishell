/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:55 by lagea             #+#    #+#             */
/*   Updated: 2024/07/29 19:04:45 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

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
		temp = NULL;
	}
	free(dll);
	dll = NULL;
}
