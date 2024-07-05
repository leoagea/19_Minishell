/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:18:44 by lagea             #+#    #+#             */
/*   Updated: 2024/07/05 17:43:54 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int expander(t_data *data)
{
	char *str;
	t_node *current;
	
	data->expander = dll_init();
	current = data->lexer->head;
	while (current != NULL)
	{
		str = current->str;
		if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, "|", 1) == 0)
		{
			printf("test\n");
		}
		// if (check_expand_error_code(current))
		current = current->next;
	}
	return 0;
}
