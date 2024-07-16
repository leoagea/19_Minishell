/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:01:04 by lagea             #+#    #+#             */
/*   Updated: 2024/07/16 16:25:26 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_double_quotes(t_data *data, char *cpy, int *i, char *str)
{
	int	start;

	*i += 1;
	start = *i;
	while (str[*i] && str[*i] != 34)
	{
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
	return (cpy);
}
