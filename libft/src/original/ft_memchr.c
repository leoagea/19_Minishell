/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:45:42 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 15:46:01 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	u_c;

	u_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == u_c)
			return ((void *)((unsigned char *)s + i));
		i++;
	}
	return (NULL);
}
