/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:51:28 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 17:02:52 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_special(char c)
{
	return ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 94)
		|| c == 96 || (c >= 123 && c <= 126));
}

char	*get_env(t_data *data, t_env_expand *env)
{
	int		i;
	int		len;
	char	*str;
	t_env	*current;

	i = 0;
	len = ft_strlen(env->var);
	current = data->env->head;
	while (current != NULL && ft_strncmp(env->var, current->var, INT_MAX) != 0)
		current = current->next;
	if (current == NULL)
		return (NULL);
	str = current->var;
	env->var_len = ft_strlen(str);
	if (len != env->var_len)
		return (NULL);
	env->expand = current->value;
	return ("");
}

char	*handle_env_variables(t_data *data, char *str, int i)
{
	char			*check;
	t_env_expand	*env;

	env = data->env_expand;
	if (!str[i + 1])
		return (NULL);
	i++;
	env->end = i;
	env->start = i;
	while ((!check_whitespace(str, i) && !check_special(str[i]) && str[i] != 34
			&& str[i] != 39) && str[i])
	{
		i++;
		env->end++;
	}
	env->var = ft_substr(str, env->start, env->end - env->start);
	check = get_env(data, env);
	if (check == NULL)
		return (NULL);
	free_str(env->var);
	return (env->expand);
}

char	*expand_env_var(t_data *data, char *cpy, int *i, char *str)
{
	char	*expand;

	if (str[*i + 1] == '?')
	{
		cpy = ft_strjoin(cpy, ft_itoa(g_exit_status));
		*i += 2;
		return (cpy);
	}
	expand = handle_env_variables(data, str, *i);
	if (expand == NULL)
		*i += data->env_expand->end - data->env_expand->start + 1;
	else
	{
		*i += data->env_expand->end - data->env_expand->start + 1;
		cpy = ft_strjoin(cpy, data->env_expand->expand);
	}
	return (cpy);
}
