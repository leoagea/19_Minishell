/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sweep_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:49:08 by lagea             #+#    #+#             */
/*   Updated: 2024/07/22 15:30:57 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*join_char(char *str, char c)
{
	int		i;
	int		len_str;
	char	*new;

	i = -1;
	if (!str)
		return (NULL);
	len_str = ft_strlen(str);
	new = malloc(sizeof(char) * (len_str + 2));
	if (!new)
		return (NULL);
	while (*str)
		new[++i] = *str++;
	new[++i] = c;
	new[++i] = '\0';
	return (new);
}

static char	*dispatch_expand(t_data *data, char *cpy, char *str, int i)
{
	while (str[i])
	{
		if (str[i] == 34)
			cpy = expand_double_quotes(data, cpy, &i, str);
		else if (str[i] == 39)
			cpy = expand_single_quotes(cpy, &i, str);
		else if (str[i] == '$')
		{
			if (str[i] == '$' && !str[i + 1])
			{
				cpy = join_char(cpy, str[i]);
				break ;
			}
			if (str[i] == '$' && ft_isdigit((int) str[i + 1]))
			{
				i += 2;
				continue;
			}
			cpy = expand_env_var(data, cpy, &i, str);
		}
		else
		{
			if (str[i - 1] == '$' && str[i - 1])
				cpy = join_char(cpy, '$');
			cpy = join_char(cpy, str[i]);
			i++;
		}
	}
	return (cpy);
}

char	*sweep_word(t_data *data, char *str)
{
	int		i;
	char	*cpy;
	t_env	*home;

	i = 0;
	cpy = ft_strdup("");
	if (ft_strncmp("~", str, 1) == 0)
	{
		home = get_node(data->env, "HOME");
		cpy = ft_strjoin(cpy, home->value);
		i++;
	}
	cpy = dispatch_expand(data, cpy, str, i);
	return (cpy);
}
