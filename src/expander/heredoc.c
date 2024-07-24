/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:18:20 by lagea             #+#    #+#             */
/*   Updated: 2024/07/16 16:28:11 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*expand_d_quotes_heredoc(char *cpy, int *i, char *str)
{
	int		start;
	char	*expand;

	*i += 1;
	start = *i;
	while (str[*i] && str[*i] != 34)
		*i += 1;
	expand = ft_substr(str, start, *i - start);
	cpy = ft_strjoin(cpy, expand);
	*i += 1;
	return (cpy);
}

char	*expand_s_quotes_heredoc(char *cpy, int *i, char *str)
{
	int		start;
	char	*expand;

	*i += 1;
	start = *i;
	while (str[*i] && str[*i] != 39)
		*i += 1;
	expand = ft_substr(str, start, *i - start);
	cpy = ft_strjoin(cpy, expand);
	*i += 1;
	return (cpy);
}

char	*expand_heredoc(char *str)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = ft_strdup("");
	while (str[i])
	{
		if (str[i] == 34)
			cpy = expand_d_quotes_heredoc(cpy, &i, str);
		else if (str[i] == 39)
			cpy = expand_s_quotes_heredoc(cpy, &i, str);
		else
		{
			cpy = join_char(cpy, str[i]);
			i++;
		}
	}
	return (cpy);
}
