/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:23:33 by lagea             #+#    #+#             */
/*   Updated: 2024/06/26 16:56:41 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_whitespace(char *str, int i)
{
	return (str[i] == ' ' || (str[i] >= (int)9 && str[i] <= 13));
}

int	check_len_token(char *str, int j)
{
	while ((ft_isalpha(str[j]) || str[j] == '|' || str[j] == '-'
			|| str[j] == '$' || str[j] == '.' || str[j] == '/' || str[j] == '>'
			|| str[j] == '<' || str[j] == '?') && str[j])
		j++;
	return j;
}

int check_quotes(char *str, int i, char quote)
{
	int j;

	j = 0;
	if (str[i] == quote)
	{
		j++;
		while (str[i + j] != quote && str[i + j])
			j++;
		j++;
	}
	return j;
}

int check_special_char(char *str, int i){
	return ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<') || str[i] == '>' || str[i] == '<');
}