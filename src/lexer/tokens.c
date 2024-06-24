/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:21:14 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 19:08:38 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int add_token(t_tokens *token)
{
	t_tokens *new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return 1;
	new->str = NULL;
	token->next = new;
	token = token->next;
	token->next = NULL;
	return 0;
}

int token_read(char *input, t_tokens *token)
{

}
