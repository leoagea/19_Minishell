/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:35:20 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 17:16:58 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*check_env_var(t_data *data, char *str, int *end, int *i)
{
	int		start;
	char	*var;
	t_env	*check;

	start = *i;
	*end = *i;
	while ((!check_whitespace(str, *i) && !check_special(str[*i])
			&& str[*i] != 34 && str[*i] != 39) && str[*i])
	{
		*i += 1;
		*end += 1;
	}
	var = ft_substr(str, start, *end - start);
	check = get_node(data->env, var);
	if (check == NULL)
		return (NULL);
	free_str(var);
	return (ft_strdup(check->value));
}

char	*check_expand(t_data *data, char *str)
{
	int		i;
	int		end;
	int		start;
	char	*value;
	char	*cpy;

	i = 0;
	cpy = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			value = check_env_var(data, str, &end, &i);
			i = start + end;
			cpy = ft_strjoin(cpy, value);
		}
		cpy = join_char(cpy, str[i]);
		i++;
	}
	return (cpy);
}
