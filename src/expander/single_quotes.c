/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:14:52 by lagea             #+#    #+#             */
/*   Updated: 2024/07/10 16:14:49 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *expand_single_quotes(t_data *data, char *cpy, int *i, char *str)
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