/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:23:33 by lagea             #+#    #+#             */
/*   Updated: 2024/06/24 21:26:00 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_whitespace(char *str, int i)
{
	while (str[i] == ' ' || (str[i] >= (int)9 && str[i] <= 13))
		i++;
	return (i);
}

int	check_len_token(char *str, int j)
{
	while ((ft_isalpha(str[j]) || str[j] == '|' || str[j] == '-'
			|| str[j] == '$' || str[j] == '.' || str[j] == '/' || str[j] == '>'
			|| str[j] == '<' || str[j] == '?') && str[j])
		j++;
	return j;
}