/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:53:07 by lagea             #+#    #+#             */
/*   Updated: 2024/07/06 12:42:40 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int check_open_pipe(t_dll *tokens)
{
	int i;

	if(ft_strncmp(tokens->tail->str, "|", 1))
		return 0;
	else
		return 1;	
}

int check_open_quote(char *str)
{
	int i;
	char quote;
	
	quote = -2 ;
	i = -1;
	while (str[++i])
		if (str[i] == 34 || str[i] == 39)
			quote = str[i];
	i = 0;
	while (str[i])
	{
		while (str[i] != quote && str[i] && quote != 0)
			i++;
		if (str[i] && quote != 0)
		{
			quote = 0;
			i++;
		}
		else
			i++;
		if ((str[i] == 34 || str[i] == 39) && str[i])
		{
			quote = str[i];
			i++;
		}
	}
	return quote;
}
