/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 22:55:59 by lagea             #+#    #+#             */
/*   Updated: 2024/07/12 00:20:57 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

t_list	*ft_lstnew(void *var, void *value, int flag)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->var = var;
	new->value = value;
	new->flag = flag;
	new->count = 0;
	new->total = 0;
	new->next = NULL;
	return (new);
}
