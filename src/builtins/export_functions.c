/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:02:16 by lagea             #+#    #+#             */
/*   Updated: 2024/07/12 21:41:06 by lagea            ###   ########.fr       */
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
	printf("check 4\n");
	return 0;	
}

int export_var_value(t_data *data, char *str)
{
	return 0;	
}

int export_cat_value(t_data *data, char *str)
{
	return 0;
}