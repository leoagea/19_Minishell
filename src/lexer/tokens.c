/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:56:36 by lagea             #+#    #+#             */
/*   Updated: 2024/08/01 17:58:52 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	in_quote(char *str, int i)
{
	char	quote;

	quote = str[i];
	i++;
	while (str[i])
	{
		while (str[i] != quote && str[i] && quote != 0)
			i++;
		quote = 0;
		i++;
		if ((str[i] == (int)34 || str[i] == (int)39) && str[i])
		{
			quote = str[i];
			i++;
		}
		else if ((check_special_char(str, i) || check_whitespace(str, i))
			&& str[i])
			return (i);
	}
	return (i);
}

static void	assign_type(t_dll *tokens)
{
	t_node	*current;

	current = tokens->head;
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
		else if (ft_strncmp(current->str, "|", 1) == 0)
			current->type = 5;
		else if (ft_strncmp(current->str, "-", 1) == 0)
			current->type = 7;
		else
			current->type = 6;
		current = current->next;
	}
}

static void	not_in_quote(char *input, int *i, int *start)
{
	if (input[*i])
	{
		*i = skip_whitespace(input, *i);
		*start = *i;
		if (check_special_char(input, *i))
			while (check_special_char(input, *i))
				*i += 1;
		else
		{
			while (!check_whitespace(input, *i) && !check_special_char(input,
					*i) && input[*i])
			{
				if ((input[*i] == (int)34 || input[*i] == (int)39) && input[*i])
					*i = in_quote(input, *i);
				else
					*i += 1;
			}
		}
	}
}

int	lexer(char *input, t_dll *tokens)
{
	int		i;
	int		start;
	char	*word;

	i = 0;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if ((input[i] == (int)34 || input[i] == (int)39) && input[i])
		{
			start = i;
			i = in_quote(input, i);
		}
		else
			not_in_quote(input, &i, &start);
		word = ft_substr(input, start, i - start);
		if (!word)
			return (1);
		if (check_open_quote(word) == 1)
			return (free(word), write(1, "Error: open quote\n", 18), 1);
		dll_insert_tail(ft_strdup(word), tokens);
		i = skip_whitespace(input, i);
		free_str(word);
	}
	return (assign_type(tokens), do_all_check(tokens));
}
