/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:12:31 by lagea             #+#    #+#             */
/*   Updated: 2024/07/03 18:17:16 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_dll *isolate_single_cmd(t_data *data, t_node *start)
{
	t_node *current;
	t_dll *single_cmd;
	
	single_cmd = dll_init();
	current = start;
	while (current != NULL)
	{
		if ((ft_strncmp(current->str, "|", 1) == 0))
			return single_cmd;
		dll_insert_tail(current->str, single_cmd);
		current = current->next;
	}
	return single_cmd;
}

int parser(t_data *data)
{
	t_dll *single_cmd;

	single_cmd = isolate_single_cmd(data, data->lexer->head); // data->lexer->head a modifier 
	printf("\n======================\n");
	dll_print_forward(single_cmd);
}

//////////////		TO DO

//faire une funct qui assigne le tyupe PIPE a tous les tokens | 

// faire une while pour isoler chaque cmd et envoyer a toutes les sub funct