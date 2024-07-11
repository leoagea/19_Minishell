/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:18:20 by lagea             #+#    #+#             */
/*   Updated: 2024/07/11 14:44:05 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char *expand_d_quotes_heredoc(t_data *data, char *cpy, int *i, char *str)
{
	int end;
	int start;
	char *expand;
	
	*i += 1;
	start = *i;
	// printf("start : %d\n", start);
	// printf("cpy : %s\n", cpy);
	while (str[*i] && str[*i] != 34)
	{
		cpy = join_char(cpy, str[*i]);
		*i += 1;
	}
	*i += 1;
	return cpy;
}

char *expand_s_quotes_heredoc(t_data *data, char *cpy, int *i, char *str)
{
	int end;
	int start;
	char *expand;
	
	*i += 1;
	start = *i;
	// printf("start : %d\n", start);
	// printf("cpy : %s\n", cpy);
	while (str[*i] && str[*i] != 39)
		*i += 1;
	expand = ft_substr(str, start, *i - start);
	cpy = ft_strjoin(cpy, expand);
	*i+= 1;
	// printf("expand : %s\n", expand);
	return cpy;
}

char *expand_heredoc(t_data *data, char *str)
{
	int i;
	int j;
	char *cpy;
	
	i = 0;
	cpy = ft_strdup("");
	while (str[i])
	{
		if (str[i] == 34)
			cpy = expand_d_quotes_heredoc(data, cpy, &i, str);
		else if (str [i] == 39)
			cpy = expand_s_quotes_heredoc(data, cpy, &i, str);
		else
		{
			cpy = join_char(cpy, str[i]);
			i++;	
		}
	}
	// printf("cpy final : %s\n", cpy);
	return cpy;
}
