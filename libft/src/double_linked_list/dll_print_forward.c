/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_print_forward.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:41:18 by lagea             #+#    #+#             */
/*   Updated: 2024/07/11 14:48:19 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	dll_print_forward(t_dll *dll)
{
	t_node	*current;

	current = dll->head;
	while (current != NULL)
	{
		ft_printf("value : %s, TYPE : %d\n", current->str, current->type);
		current = current->next;
	}
}
