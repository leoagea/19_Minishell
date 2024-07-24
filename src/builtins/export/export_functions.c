/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:02:16 by lagea             #+#    #+#             */
/*   Updated: 2024/07/23 13:47:54 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	export_var(t_data *data, char *str)
{
	t_env	*check;
	t_env	*node;

	printf("check\n");
	check = data->env->head;
	while (check)
	{
		if (ft_strncmp(check->var, str, INT_MAX) == 0)
			return (1);
		check = check->next;
	}
	node = lst_new(str, NULL, 0);
	if (!node)
		return (1);
	lst_insert_tail(node, data->env);
	printf("check 1\n");
	return (0);
}

int	export_var_value(t_data *data, char *str)
{
	int		i;
	int		start;
	char	*var;
	char	*value;
	t_env	*node;

	i = -1;
	while (str[++i] != '=')
		;
	var = ft_substr(str, 0, i);
	start = ++i;
	while (str[i])
		i++;
	value = ft_substr(str, start, i - start);
	node = get_node(data->env, var);
	if (node)
	{
		node->value = value;
		return 0;
	}
	node = lst_new(var, value, 1);
	if (!node)
		return (1);
	lst_insert_tail(node, data->env);
	return (0);
}

int	export_cat_value(t_data *data, char *str)
{
	int		i;
	int		start;
	char	*var;
	char	*value;
	t_env	*current;

	i = 0;
	while (str[++i] != '+')
		;
	var = ft_substr(str, 0, i);
	if (!var)
		return (1);
	current = get_node(data->env, var);
	start = i + 2;
	while (str[++i])
		;
	value = ft_substr(str, start, i - start);
	if (!value)
		return (1);
	if (!current->value)
		current->value = ft_strdup("");
	current->value = ft_strjoin(current->value, value);
	if (!current->value)
		return (1);
	return (0);
}
