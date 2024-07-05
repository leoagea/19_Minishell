/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:53:07 by lagea             #+#    #+#             */
/*   Updated: 2024/07/05 17:52:08 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_open_pipe(t_dll *tokens)
{
	if (ft_strncmp(tokens->tail->str, "|", 1))
		return (0);
	return (1);
}

int	check_open_quote(char *str)
{
	int		i;
	char	quote;

	quote = -2;
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
	return (quote);
}

int	check_open_redirect(t_dll *tokens)
{
	char *str;

	str = tokens->tail->str;
	if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0
		|| ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, "<", 1) == 0
		|| ft_strncmp(str, "|", 1) == 0)
		return (1);
	return (0);
}
