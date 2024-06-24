/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:03:36 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 15:53:34 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

static void	print_unb(unsigned int n, int fd)
{
	if (n / 10)
	{
		print_unb(n / 10, fd);
		print_unb(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}

void	ft_putunbr_fd(unsigned int n, int fd)
{
	unsigned long	nbr;

	if (fd < 0)
		return ;
	nbr = (unsigned long)n;
	print_unb(nbr, fd);
}
