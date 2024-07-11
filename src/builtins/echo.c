/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:17:04 by lagea             #+#    #+#             */
/*   Updated: 2024/07/11 18:26:07 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int check_flag(char *str)
{
	int i;
	
	i = 0;
	while ((str[i] == '-' || str[i] == 'n') && str[i])
		i++;
	i++;
	if (str[i] == '\0')
		return 1;
	return 0;		
}

void check_option(char **str, int *flag)
{
	int i = 1;
	while (str[i])
	{
		if (ft_strncmp(str[i],"-",1))
		{
			if (check_flag(str[i]))
				*flag += 1;
		}
		else
			return ;
		i++;
	}
}

int echo(t_cmd *cmd)
{
	int flag;
	char **str;
	
	flag = 0;
	str = cmd->str;
	check_option(str, &flag);
	printf("flag : %d", flag);
	return 0;
}