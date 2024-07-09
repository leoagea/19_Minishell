/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:51:28 by lagea             #+#    #+#             */
/*   Updated: 2024/07/09 16:11:54 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char *get_env_var(t_data *data, t_env_expand *env)
{
	int i;
	int len;
	char *str;
	t_list *current;
	
	i = 0;
	len = ft_strlen(env->var);
	current = data->env;
	// printf("current content : %s\n", current->content);
	// printf("env var : %s÷\n", env->var);
	// printf("len : %d\n",len);
	while (current != NULL && ft_strncmp(env->var, current->content, len) != 0)
	{
		// printf("current : %s\n", current->content);
		current = current->next;
		// if (current == NULL)
		// 	break;	
	}
	// if (ft_strncmp(env->var, current->next->content, len) == 0);
	// 	current = current->next;
	// printf("test\n");
	if (current == NULL)
		return NULL;
	str = current->content;
	env->var_len = ft_strlen(str);
	while (str[i] != '=' && str[i])
		i++;
	env->sub = i;
	len = ft_strlen(env->var);
	// printf("env var_len : %d\nenv sub : %d\n", env->var_len, env->sub);
	if (len != env->sub)
		return NULL;
	env->expand = ft_substr(str, env->sub + 1, env->var_len - env->sub);
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
	while ((!check_whitespace(str, i) && str[i] != '$' )  && str[i])
	{
		// printf("2\n");
		i++;
		// printf("boucle len : %s\n", str + i);
		env->end++;
	}
	// printf("start : %d, end : %d\n", env->start, env->end);
	env->var = ft_substr(str, env->start, env->end - env->start);
	// printf("env total : %d, count : %d\n", data->env->total, data->env->count); 
	check = get_env_var(data, env);
	if (check == NULL)
		return NULL;
	// printf("var : %s\n", env->var);
	// printf("expand : %s\n", env->expand);
	return env->expand;
}

//echo $USER