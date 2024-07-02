/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:23:33 by lagea             #+#    #+#             */
/*   Updated: 2024/07/02 16:02:05 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_whitespace(char *str, int i)
{
	return (str[i] == ' ' || (str[i] >= (int)9 && str[i] <= 13));
}

int	check_special_char(char *str, int i)
{
	return ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
			+ 1] == '<') || str[i] == '>' || str[i] == '<' || str[i] == '|');
}

// int fill_in_dll(t_dll *dll, char *str)
// {

// 	dll_insert_tail(str, dll);
// }