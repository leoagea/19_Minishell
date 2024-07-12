/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:51:28 by lagea             #+#    #+#             */
/*   Updated: 2024/07/12 15:54:44 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int check_special(char c)
{
	return ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 94) || c == 96 || (c >= 123 && c <= 126));
}

static char *get_env_var(t_data *data, t_env_expand *env)
{
	int i;
	int len;
	char *str;
	t_env *current;
	
	i = 0;
	len = ft_strlen(env->var);
	current = data->env->head;
	// printf("current content : %s\n", current->content);
	// printf("env var : %s÷\n", env->var);
	// printf("len : %d\n",len);
	while (current != NULL && ft_strncmp(env->var, current->var, INT_MAX) != 0)
		current = current->next;
	if (current == NULL)
		return NULL;
	str = current->var;
	env->var_len = ft_strlen(str);
	// printf("env var_len : %d\nenv sub : %d\n", env->var_len, env->sub);
	if (len != env->var_len)
		return NULL;
	env->expand = current->value;
	// printf("env expand : %s\n", env->expand);
	return "";
}

char *handle_env_variables(t_data *data, char *str, int i)
{
	char *check;
	t_env_expand *env;
	
	env = data->env_expand;
	if (!str[i + 1])
		return NULL;
	i++;		
	env->end = i;
	env->start = i;
	// printf("check \n");
	while ((!check_whitespace(str, i) && !check_special(str[i]) && str[i] != 34 && str[i] != 39)  && str[i])
	{
		// printf("2\n");
		i++;
		// printf("boucle len : %s\n", str + i);
		env->end++;
	}
	// printf("start : %d, end : %d\n", env->start, env->end);
	env->var = ft_substr(str, env->start, env->end - env->start);
	// printf("env total : %d, count : %d\n", data->env->total, data->env->count); 
	// printf("var : %s\n", env->var);
	check = get_env_var(data, env);
	if (check == NULL)
		return NULL;
	// printf("var : %s\n", env->var);
	// printf("expand : %s\n", env->expand);
	return env->expand;
}

char *expand_env_var(t_data *data, char *cpy, int *i, char *str)
{
	char *expand;
	
	if (str[*i + 1] == '?')
	{
		cpy = ft_strjoin(cpy, ft_itoa(g_exit_status));
		*i+= 2;
		return cpy;
	}
	// printf("test 3\n");
	expand = handle_env_variables(data, str, *i);
	if (expand == NULL)
		*i += data->env_expand->end - data->env_expand->start + 1;
	else
	{
		*i += data->env_expand->end - data->env_expand->start + 1;
		cpy = ft_strjoin(cpy, data->env_expand->expand);
	}
	return cpy;
}
//echo $USER