/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:53:07 by lagea             #+#    #+#             */
/*   Updated: 2024/07/03 13:38:03 by lagea            ###   ########.fr       */
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
	
	quote = 'x';
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
