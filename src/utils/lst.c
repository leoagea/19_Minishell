/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 01:48:14 by lagea             #+#    #+#             */
/*   Updated: 2024/07/13 02:00:13 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//export = 1 -> value exported otherwise value by default
t_env	*lst_new(char *var, char *value, int flag)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = var;
	new->value = value;
	new->flag = flag;
	new->next = NULL;
	return (new);
}

void	lst_insert_tail(t_env *new, t_lst *lst)
{
	if (lst->tail == NULL)
	{
		lst->head = new;
		lst->tail = new;
	}
	else
	{
		lst->tail->next = new;
		lst->tail = new;
	}
}

int    lst_size(t_lst *lst)
{
    int size;
    t_env *current;

    size = 0;
    if(!lst)
        return size;
    printf("check\n");
    current = lst->head;
    while(current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}