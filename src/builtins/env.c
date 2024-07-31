/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:21:18 by lagea             #+#    #+#             */
/*   Updated: 2024/07/30 15:47:37 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*mode = 1 ==> env / mode != 1 ==> only export */
int	print_env(t_lst *env)
{
	t_env	*node;

	if (!env)
		return 1;
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
