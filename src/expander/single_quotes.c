/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:14:52 by lagea             #+#    #+#             */
/*   Updated: 2024/07/29 13:03:41 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_single_quotes(char *cpy, int *i, char *str)
{
	int		start;
	char	*expand;

	*i += 1;
	start = *i;
	while (str[*i] && str[*i] != 39)
		*i += 1;
	expand = ft_substr(str, start, *i - start);
	cpy = ft_strjoin(cpy, expand);
	free_str(expand);
	*i += 1;
	return (cpy);
}
