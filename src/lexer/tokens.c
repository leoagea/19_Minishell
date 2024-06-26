/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:21:14 by lagea             #+#    #+#             */
/*   Updated: 2024/06/26 17:22:54 by lagea            ###   ########.fr       */
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
		i = check_whitespace(input, i);
		// printf("i : %d\n",i);
		j = 0;
		j += check_quotes(input, i, (int) 34);
		j += check_quotes(input, i, (int) 39);
		if (j == 0)
			j = check_len_token(input, i);
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
	return 0;
}

int	token_read(char *input, t_tokens *token)
{
	// int i;
	// char **split;
	// t_tokens *head;

	// head = token;
	// i = 0;
	// // split = ft_split_minishell(input, '|');
	// while (split[i] != NULL)
	// {
	// 	printf("chaine splite, i : %d , str : %s\n", i, split[i]);
	// 	// read_without_quote(split[i], token);
	// 	i++;
	// }
	
	// int i = check_quotes(input, 0, (int) 34);
	// printf("end quotes : %d\n",i);
	// printf("char next to quote : %c\n", (int) 34);
	// printf("char next to quote : %c\n", (int) 39);
	
	read_without_quote(input, token);
}
//echo | cat > infile -e | pwd

//flag in quot

//tant que tu ne voie pas un | > < >> << un wihtespacec c est le meme token