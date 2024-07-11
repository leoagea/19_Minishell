/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:29:55 by lagea             #+#    #+#             */
/*   Updated: 2024/07/11 14:52:54 by vdarras          ###   ########.fr       */
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
		ft_printf("str : %s\n", current->str[0]);
		ft_printf("redirections : %d\n", current->num_redirections);
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
}

int	dll_cmd_size(t_dll_cmd *dll)
{
	int	dll_len;
	t_cmd	*current;

	dll_len = 0;
	current = dll->head;
	while (current != NULL)
	{
		dll_len++;
		current = current->next;
	}
	return (dll_len);
}