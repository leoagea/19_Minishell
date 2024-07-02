/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_print_forward.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:41:18 by lagea             #+#    #+#             */
/*   Updated: 2024/07/02 16:02:16 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	dll_print_forward(t_dll *dll)
{
	t_node	*current;

	current = dll->head;
	while (current != NULL)
	{
		ft_printf("value : %s\n", current->str);
		current = current->next;
	}
}
