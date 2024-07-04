/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:29:55 by lagea             #+#    #+#             */
/*   Updated: 2024/07/04 17:37:04 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*dll_cmd_new_node(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->str = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->redirections = NULL;
	new->num_redirections = 0;
	return (new);
}

void	dll_cmd_clear(t_dll_cmd *dll)
{
	t_cmd	*temp;
	t_cmd	*current;

	if (!dll)
		return ;
	current = dll->head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

void	dll_cmd_insert_tail(t_dll_cmd *dll, t_cmd *new)
{
	if (new == NULL)
	{
		dll_cmd_clear(dll);
		return ;
	}
	if (dll->tail == NULL)
	{
		dll->head = new;
		dll->tail = new;
	}
	else
	{
		new->prev = dll->tail;
		dll->tail->next = new;
		dll->tail = new;
	}
}


void	dll_cmd_print_forward(t_dll_cmd *dll)
{
	t_cmd	*current;

	current = dll->head;
	while (current != NULL)
	{
		ft_printf("nbr redirections : %d\n", current->num_redirections);
		ft_printf("redirections : %s\n", current->str);
		current = current->next;
	}
}

void dll_delete_node(t_node *delete)  
{  
    t_node *ptr;   
	 
    ptr = delete;  
    delete->prev->next = ptr->next;  
    ptr->next->prev = delete->prev;  
	free(ptr);  
	printf("\nNode Deleted\n");  
}
