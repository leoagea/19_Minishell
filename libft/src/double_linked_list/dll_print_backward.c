/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_print_backward.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:38:24 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 13:02:07 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	dll_print_backward(t_dll *dll)
{
	t_node	*current;

	current = dll->tail;
	while (current != NULL)
	{
		ft_printf("value : %d\n", current->value);
		current = current->prev;
	}
}
