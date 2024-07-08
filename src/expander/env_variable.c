/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:51:28 by lagea             #+#    #+#             */
/*   Updated: 2024/07/08 19:35:33 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *handle_env_variables(t_data *data, char *str, int i)
{
	t_env_expand *env;

	env = data->env_expand;
	if (str[i + 1])
		i++;
	env->start = i;
	while (!check_whitespace(str, i) && str[i])
	{
		printf("2\n");
		i++;
		env->end++;
	}
	printf("start : %d, end : %d\n", env->start, env->end);
	env->var = ft_substr(str, env->start, env->end);
	return env;
}

//echo $USER