/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:40:47 by lagea             #+#    #+#             */
/*   Updated: 2024/07/04 15:29:14 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int handle_redirections(t_dll *single_cmd, t_data *data)
{
	t_cmd *cmd;
	t_node *current;
	
	current = single_cmd->head;
	cmd = dll_cmd_new_node();
	// printf("test\n");
	dll_cmd_insert_tail(data->parser, cmd);
	cmd->redirections = dll_init();
	while (current != NULL)
	{
		// printf("test 2\n");
		// printf("current type : %d\n", current->type);
		if (current->type == 1 || current->type  == 2 || current->type == 3 || current->type == 4)
		{
			// printf("test 1\n");
			cmd->num_redirections++;
			dll_insert_tail(current->next->str, cmd->redirections);
			cmd->redirections->tail->type = current->type;
			// dll_print_forward(cmd->redirections);
			printf("file : %s ; type : %d\n", cmd->redirections->tail->str, cmd->redirections->tail->type);
		}
		current = current->next;
	}
}

// cat -e | ls -la |echo "test"
//!(ft_strncmp(current->str, "|", 1) == 0)


// cmd puis option puis arg