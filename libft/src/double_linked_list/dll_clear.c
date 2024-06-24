/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:30:55 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 13:00:22 by vdarras          ###   ########.fr       */
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
	}
	free(dll);
}
