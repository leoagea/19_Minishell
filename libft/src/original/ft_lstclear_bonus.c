/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 22:49:46 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 13:18:42 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*current;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		temp = current;
		current = current->next;
		del(temp->content);
		free(temp);
	}
	*lst = NULL;
}
