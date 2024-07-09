/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:01:04 by lagea             #+#    #+#             */
/*   Updated: 2024/07/09 17:40:23 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *expand_double_quotes(t_data *data, char *cpy, int *i, char *str)
{
	int end;
	int start;
	char *expand;
	
	*i += 1;
	start = *i;
	printf("start : %d\n", start);
	printf("cpy : %s\n", cpy);
	while (str[*i] && str[*i] != 34)
	{
		printf("test\n");
		// if (str[*i] == '$')
		// 	cpy = expand_env_var(data, cpy, i, str);
		// else
			*i+= 1;
	}
	end = *i;
	expand = ft_substr(str, start, end - start);
	cpy = ft_strjoin(cpy, expand);
	*i += 1;
	printf("expand : %s\n", expand);
	printf("end : %d\n", end);
}
