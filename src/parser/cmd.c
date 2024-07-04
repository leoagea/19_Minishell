/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:12:31 by lagea             #+#    #+#             */
/*   Updated: 2024/07/04 13:24:21 by lagea            ###   ########.fr       */
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

void assign_type(t_data *data)
{
	t_node *current;

	current = data->lexer->head;
	while (current != NULL)
	{
		if (ft_strncmp(current->str, ">>", 2) == 0)
			current->type = 4;	
		else if (ft_strncmp(current->str, "<<", 2) == 0)
			current->type = 3;
		else if (ft_strncmp(current->str, ">", 1) == 0)
			current->type = 2;
		else if (ft_strncmp(current->str, "<", 1) == 0)
			current->type = 1;	
		else if (ft_strncmp(current->str, "|", 2) == 0)
			current->type = 5;
		else if (ft_strncmp(current->str, "-", 1) == 0)
			current->type = 7;
		current = current->next;
	}
}

int parser(t_data *data)
{
	t_node *current;
	t_dll *single_cmd;
	
	assign_type(data);
	current = data->lexer->head;
	printf("\n======================\n");
	while (current != NULL)
	{
		single_cmd = isolate_single_cmd(data, current);
		dll_print_forward(single_cmd);
		printf("\n======================\n");
		while (current != NULL && current->type != PIPE){
			current = current->next;
		}
		if (current != NULL && current->type == PIPE)
			current = current->next;
		// if (current->next != NULL)
		// 	current = current->next;
	}
}

// cat -e | ls -la |echo "test" | pwd | cat < Makefile > test.txt


//////////////		TO DO

//faire une funct qui assigne le tyupe PIPE a tous les tokens | 

// faire une while pour isoler chaque cmd et envoyer a toutes les sub funct