/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:17:04 by lagea             #+#    #+#             */
/*   Updated: 2024/07/16 17:19:31 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_flag(char *str)
{
	int	i;

	i = 1;
	while (str[i] == 'n' && str[i])
		i++;
	i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	check_option(char **str)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[i], "-", 1))
		{
			if (check_flag(str[i]))
				flag++;
		}
		else
			return (flag);
		i++;
	}
	return (flag);
}

int	echo(t_cmd *cmd)
{
	int		i;
	int		flag;
	char	**str;

	str = cmd->str;
	flag = check_option(str);
	i = flag + 1;
	while (str[i])
	{
		write(STDOUT_FILENO, str[i], ft_strlen(str[i]));
		if (str[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
