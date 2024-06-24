/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:23:35 by lagea             #+#    #+#             */
/*   Updated: 2024/06/18 15:04:01 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	lstsize;

	lstsize = 0;
	while (lst != (void *)0)
	{
		lstsize++;
		lst = lst->next;
	}
	return (lstsize);
}
