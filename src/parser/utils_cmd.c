/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:29:55 by lagea             #+#    #+#             */
/*   Updated: 2024/07/31 20:21:14 by vdarras          ###   ########.fr       */
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
	new->num_cmd = 0;
	return (new);
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
	char	**str;
	t_cmd	*current;
	int		i;

	current = dll->head;
	while (current != NULL)
	{
		str = current->str;
		i = 0;
		while (str[i])
		{
			ft_printf("str : %s\n", current->str[i]);
			i++;
		}
		printf("---------------\n");
		dll_print_forward(current->redirections);
		printf("---------------\n");
		current = current->next;
		printf("========================\n");
	}
}

void	dll_delete_node(t_node *delete)
{
	t_node	*ptr;

	ptr = delete;
	delete->prev->next = ptr->next;
	ptr->next->prev = delete->prev;
	free(ptr);
}

int	dll_cmd_size(t_dll_cmd *dll)
{
	int		dll_len;
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
