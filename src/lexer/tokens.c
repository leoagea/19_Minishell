/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:21:14 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 21:29:19 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_token(t_tokens *token)
{
	t_tokens	*new;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (1);
	new->str = NULL;
	token->next = new;
	token = token->next;
	token->next = NULL;
	return (0);
}

int read_without_quote(char *input, t_tokens *token)
{
	int	i;
	int	j;

	i = 0;
	token = malloc(sizeof(t_tokens));
	while (input[i])
	{
		i = skip_whitespace(input, i);
		// printf("i : %d\n",i);
		j = i;
		j = check_len_token(input, j);
		// printf("j : %d\n",j);
		token->str = ft_substr(input, i, j - i);
		if (!token->str)
			return (1);
		if (add_token(token))
			return (1);
		printf("str : %s\n", token->str);
		token = token->next;
		i = j;
		i++;
	}
}

int	token_read(char *input, t_tokens *token)
{
	read_without_quote(input, token);
}
