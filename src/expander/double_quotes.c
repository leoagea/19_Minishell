/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:01:04 by lagea             #+#    #+#             */
/*   Updated: 2024/07/10 16:27:22 by lagea            ###   ########.fr       */
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
	// printf("start : %d\n", start);
	// printf("cpy : %s\n", cpy);
	while (str[*i] && str[*i] != 34)
	{
		// printf("test\n");
		if (str[*i] == '$')
			cpy = expand_env_var(data, cpy, i, str);
		else
		{
			if (str[*i - 1] == '$' && str[*i - 1])
				cpy = join_char(cpy, '$');
			cpy = join_char(cpy, str[*i]);
			*i += 1;
		}
	}
	*i += 1;
	return cpy;
}
