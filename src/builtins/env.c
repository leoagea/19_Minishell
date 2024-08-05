/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:21:18 by lagea             #+#    #+#             */
/*   Updated: 2024/08/01 17:27:49 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_env(t_lst *env)
{
	t_env	*node;

	if (!env)
		return (1);
	node = env->head;
	while (node != NULL)
	{
		if (node->flag == 1)
		{
			ft_printf("%s=", node->var);
			if (node->value)
				ft_printf("%s\n", node->value);
		}
		node = node->next;
	}
	return (0);
}
