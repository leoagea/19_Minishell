/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 00:17:32 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 15:46:01 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	index;

	index = 0;
	if (!s || !f)
		return ;
	while (s[index])
	{
		(*f)(index, s + index);
		index++;
	}
}
