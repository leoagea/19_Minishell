/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:53:07 by lagea             #+#    #+#             */
/*   Updated: 2024/07/11 14:48:24 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_open_pipe(t_dll *tokens)
{
	if (tokens->tail->type == PIPE)
		return (1);
	if (tokens->head->type == PIPE)
		return 1;
	return (0);
}

bool check_open_quote(const char *str)
{
    bool single_quote_open = false;
    bool double_quote_open = false;

    while (*str)
    {
        if (*str == '\'' && !double_quote_open)
        {
            single_quote_open = !single_quote_open;
        }
        else if (*str == '\"' && !single_quote_open)
        {
            double_quote_open = !double_quote_open;
        }
        str++;
    }
    return single_quote_open || double_quote_open;
}

int	check_open_redirect(t_dll *tokens)
{
	char *str;

	str = tokens->tail->str;
	if (ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, "<<", 2) == 0
		|| ft_strncmp(str, ">", 1) == 0 || ft_strncmp(str, "<", 1) == 0)
		return (1);
	return (0);
}

int check_wrong_token(t_dll *tokens)
{
	char *str;
	t_node *current;

	current = tokens->head;
	while (current != NULL){
		str = current->str;
		if (ft_strncmp(str, ">>>", 3) == 0 || ft_strncmp(str, "<<<", 3) == 0 || ft_strncmp(str, "||", 2) == 0)
			return 1;
		current = current->next;
	}
	return 0;	
}