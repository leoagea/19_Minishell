/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:18:44 by lagea             #+#    #+#             */
/*   Updated: 2024/07/09 16:11:31 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char *join_char(char *str, char c)
{
	int i;
	int len_str;
	char *new;

	i = -1;
	if (!str)
		return NULL;
	printf("str input join_char : %s\n", str);
	len_str = ft_strlen(str);
	new = malloc(sizeof(char) * (len_str + 2));
	if (!new)
		return NULL;
	while (*str)
		new[++i] = *str++;
	new[++i] = c;
	new[++i] = '\0';
	return new;
}

static void sweep_word(t_data *data, char *str, t_node *current)
{
	int i;
	int j;
	char *cpy = ft_strdup("");
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
			// printf("Test\n");
			expand = handle_env_variables(data, str, i);
			// printf("Test segfault 2\n");
			// printf("env sub : %d\n", data->env_expand->sub);
			// printf("env start : %d\n", data->env_expand->start);
			// printf("env end : %d\n", data->env_expand->end);
			// printf("env var_len : %d\n", data->env_expand->var_len);
			if (expand == NULL)
			{
				printf("NULL\n");
				i += data->env_expand->end - data->env_expand->start;
			}
			else{
				// printf("start : %d, end : %d\n", data->env_expand->start, data->env_expand->end);
				i += data->env_expand->sub ;
				// printf("expand sweep word : %s\n", data->env_expand->expand);
				cpy = ft_strjoin(cpy, data->env_expand->expand);
			}
			// printf("i : %d, char : %c\n",i, str[i]); 
		}
		else
			cpy = join_char(cpy, str[i]);
			i++;
	}
	printf("cpy final : %s\n", cpy);
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
			// printf("test ");
			// printf("%s\n", str);
			sweep_word(data, str, current);
		}
		current = current->next;
	}
	return 0;
}
