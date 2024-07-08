/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:18:44 by lagea             #+#    #+#             */
/*   Updated: 2024/07/08 19:16:53 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void sweep_word(t_data *data, char *str, t_node *current)
{
	int i;
	char cpy;
	char *expand;
	i = 0;
	data->env_expand = env_var_init();
	while (str[i])
	{
		// if (str[i] == 34)
		// 	expand = handle_double_quotes(str, i);
		// else if (str [i] == 39)
		// 	expand = handle_single_quotes(str, i);
		if (str[i] == '$')
		{
			printf("1\n");
			expand = handle_env_variables(data, str, i);
		}
		i++;
	}
}

//avancer dans le word , si on rrentre dans auncuin if copie str[i] dans la cpy
// modifie le i par pointeur
// si $ on expand la variable de la bonne taille
// puis on join sur la cpy

int expander(t_data *data)
{
	char *str;
	t_node *current;
	
	data->expander = dll_init(); 
	current = data->lexer->head;
	while (current != NULL)
	{
		str = current->str;
		if (current->type != PIPE && current->type != INPUT && current->type != TRUNC && current->type != HEREDOC && current->type != APPEND)
		{
			printf("test ");
			printf("%s\n", str);
			sweep_word(data, str, current);
		}
		current = current->next;
	}
	return 0;
}
