/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 23:23:35 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 13:18:42 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

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
