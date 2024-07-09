/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:12:31 by lagea             #+#    #+#             */
/*   Updated: 2024/07/09 12:58:21 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_dll *isolate_single_cmd(t_data *data, t_node *start)
{
	t_node *current;
	t_node *currend_cmd;
	t_dll *single_cmd;
	
	single_cmd = dll_init();
	current = start;
	while (current != NULL)
	{
		if (current->type == PIPE)
			return single_cmd;
		dll_insert_tail(current->str, single_cmd);
		currend_cmd = single_cmd->tail;
		currend_cmd->type = current->type;
		current = current->next;
	}
	return single_cmd;
}

static void assign_type(t_data *data)
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

static int put_in_str(t_data *data, t_dll *cmd)
{
	int i;
	int nb_tokens;
	t_node *current;

	i = 0;
	current = cmd->head;
	nb_tokens = dll_size(cmd);
	data->parser->tail->str = malloc(sizeof(char *) * nb_tokens + 1);
	if (dll_size(cmd) == 0)
		return 1;
	while (current != NULL)
	{
;		data->parser->tail->str[i] = current->str;
		current = current->next;
		i++;
	}handle_signal();
	data->parser->tail->str[i] = NULL;
}

int parser(t_data *data)
{
	t_node *current;
	t_dll *single_cmd;
	
	assign_type(data);
	current = data->lexer->head;
	while (current != NULL)
	{
		single_cmd = isolate_single_cmd(data, current);
		// dll_print_forward(single_cmd);
		handle_redirections(single_cmd, data);
		while (current != NULL && current->type != PIPE){
			current = current->next;
		}
		if (current != NULL && current->type == PIPE)
			current = current->next;
		put_in_str(data, single_cmd);
		// dll_print_forward(single_cmd);
		// printf("\n======================\n");
		// printf("double array cmd : \n");
		// int i = 0;
		// while(data->parser->tail->str[i] != NULL){
		// 	printf("str [%d] : %s\n", i, data->parser->tail->str[i]);
		// 	i++;
		// }
	}
}

// cat -e | ls -la |echo "test" | pwd | cat < Makefile > test.txt


//////////////		TO DO

//faire une funct qui assigne le tyupe PIPE a tous les tokens | 

// faire une while pour isoler chaque cmd et envoyer a toutes les sub funct