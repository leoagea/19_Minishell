/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:21:33 by lagea             #+#    #+#             */
/*   Updated: 2024/07/29 18:46:43 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <unistd.h>

char	*get_pwd(void)
{
	int		i;
	int		len;
	char	*pwd;
	char	buffer[BUFFER_SIZE];

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	return (pwd);
}

int	pwd(void)
{
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("Error :", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free_str(pwd);
	return (0);
}
