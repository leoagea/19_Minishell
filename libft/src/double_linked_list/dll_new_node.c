/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_new_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:23:41 by lagea             #+#    #+#             */
/*   Updated: 2024/06/18 14:49:14 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_node	*dll_new_node(int data)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->value = 0;
	new->value = data;
	new->col = 0;
	new->line = 0;
	new->color = 0xFFFFFF;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
