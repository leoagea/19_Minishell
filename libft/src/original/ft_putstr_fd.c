/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:55:48 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 15:46:01 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	length;

	length = 0;
	if (!s || fd < 0)
		return ;
	while (s[length])
		length++;
	write(fd, s, length);
}
