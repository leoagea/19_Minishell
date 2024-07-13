/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:02:16 by lagea             #+#    #+#             */
/*   Updated: 2024/07/13 02:35:22 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int export_var(t_data *data, char *str)
{
	t_env *node;

	node = lst_new(str, NULL, 0);
	if (!node)
		return 0;
	lst_insert_tail(node, data->env);
	return 0;	
}

int export_var_value(t_data *data, char *str)
{
	int i;
	int start;
	char *var;
	char *value;
	t_env *node;

	i = -1;
	while(str[++i] != '=');
	var = ft_substr(str, 0, i);
	start = ++i;
	while (str[i])
	i++;
	value = ft_substr(str, start, i - start);
	node = lst_new(var, value, 1);
	if (!node)
		return 1;
	lst_insert_tail(node, data->env);
	return 0;	
}

int export_cat_value(t_data *data, char *str)
{
	int i;
	int start;
	char *var;
	char *value;
	t_env *node;
	t_env *current;
	
	i = 0;
	while(str[++i] != '+');
	var = ft_substr(str, 0, i);
	if (!var)
		return 1;
	current = data->env->head;
	while (current != NULL && ft_strncmp(var, current->var, INT_MAX) != 0)
		current = current->next;
	start = i + 2;
	while(str[++i]);
	value = ft_substr(str, start, i - start);
	if (!value)
		return 1;
	current->value = ft_strjoin(current->value, value);
	if (!current->value)
		return 1;
	return 0;
}

void sort_export(t_lst *export) //segfault a corriger
{
    const int size=lst_size(export);
	int i;
    t_env *node;
    t_env *node2 = NULL;

	printf("check 1\n");
	i = 0;
	while(i < size)
	{
		node = export->head;
		while(node->next != node2)
		{
			printf("check 2\n");
			if (ft_strncmp(node->value, node->next->value, INT_MAX) < 0)
				swap_node(node, node->next, export);
			node = node->next;
		}
		node2 = node;
	}
	printf("check 3\n");
	node = export->head;
	printf("check 4\n");
	while (node != NULL)
	{
		printf("%s\n", node->var);
		node = node->next;
	}
	printf("check 5\n");
}
