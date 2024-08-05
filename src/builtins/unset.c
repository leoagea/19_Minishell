/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:21:37 by lagea             #+#    #+#             */
/*   Updated: 2024/07/29 13:03:05 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	lst_delete_node(t_env *prev, t_env *delete, t_lst *lst)
{
	if (!prev)
	{
		lst->head = delete->next;
		if (delete == lst->tail)
			lst->tail = NULL;
	}
	else
	{
		prev->next = delete->next;
		if (delete == lst->tail)
			lst->tail = prev;
	}
	if (delete->value)
	{
		free_str(delete->value);
		delete->value = NULL;
	}
	free_str(delete->var);
	delete->var = NULL;
	free(delete);
}

static int	unset_var(t_lst *env, char *var)
{
	t_env	*node;
	t_env	*prev;

	node = env->head;
	prev = NULL;
	while (node)
	{
		if (strncmp(node->var, var, INT_MAX) == 0)
		{
			lst_delete_node(prev, node, env);
			return (0);
		}
		prev = node;
		node = node->next;
	}
	return (0);
}

static int	dispatch_unset(t_data *data, char *str, int j)
{
	int	return_value;

	return_value = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		return_value = 1;
		ft_printf("bash: unset: `%s': not a valid identifier\n", str);
	}
	else if (str[j] == '\0')
		return_value = unset_var(data->env, str);
	else
	{
		return_value = 1;
		ft_printf("bash: unset: `%s': not a valid identifier\n", str);
	}
	return (return_value);
}

int	unset(t_data *data, t_cmd *cmd)
{
	int		i;
	int		j;
	int		return_value;
	char	**arr;
	char	*str;

	i = 1;
	arr = cmd->str;
	return_value = 0;
	while (arr[i])
	{
		j = 0;
		str = arr[i];
		while (str[j] && (ft_isalnum((int)str[j]) == 1 || str[j] == '_'))
			j++;
		return_value = dispatch_unset(data, str, j);
		i++;
	}
	return (return_value);
}
