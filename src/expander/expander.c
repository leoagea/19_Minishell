/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:18:44 by lagea             #+#    #+#             */
/*   Updated: 2024/07/15 17:46:51 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *join_char(char *str, char c)
{
	int i;
	int len_str;
	char *new;

	i = -1;
	if (!str)
		return NULL;
	// printf("str input join_char : %s\n", str);
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

static char *sweep_word(t_data *data, char *str)
{
	int i;
	char *cpy;
	t_env *home;
	
	i = 0;
	cpy = ft_strdup("");
	if (ft_strncmp("~", str, 1) == 0)
	{
		home = get_node(data->env, "HOME");
		cpy = ft_strjoin(cpy, home->value);
		i++;
	}
	while (str[i])
	{
		if (str[i] == 34)
			cpy = expand_double_quotes(data, cpy, &i, str);
		else if (str [i] == 39)
			cpy = expand_single_quotes(cpy, &i, str);
		else if (str[i] == '$')
		{
			if (str[i] == '$' && !str[i + 1])
			{
				cpy = join_char(cpy, str[i]);
				break;
			}
			// printf("test env\n");
			cpy = expand_env_var(data, cpy, &i, str);
		}
		else
		{
			if (str[i - 1] == '$' && str[i - 1])
				cpy = join_char(cpy, '$');
			cpy = join_char(cpy, str[i]);
			i++;	
		}
	}
	// printf("cpy final : %s\n", cpy);
	return cpy;
}

int expander(t_data *data)
{
	char *str;
	char *cpy;
	t_node *current;
	
	data->expander = dll_init(); 
	data->env_expand = env_var_init();
	current = data->lexer->head;
	// printf("test 1\n");
	while (current != NULL)
	{
		str = current->str;
		// printf("test 2\n");
		if (current->type != PIPE && current->type != INPUT && current->type != TRUNC && current->type != APPEND && current->type != HEREDOC)
		{
			// printf("test \n");
			// printf("%s\n", str);
			cpy = sweep_word(data, str);
			dll_insert_tail(cpy, data->expander);
			data->expander->tail->type = current->type;
		}
		else if (current->type == HEREDOC)
		{
			dll_insert_tail(cpy, data->expander);
			data->expander->tail->type = current->type;
			current = current->next;
			// printf("test \n");
			cpy = expand_heredoc(current->str);
			// printf("cpy : %s\n", cpy);
			dll_insert_tail(cpy, data->expander);
			data->expander->tail->type = current->type;
		}
		else 
		{
			dll_insert_tail(current->str, data->expander);
			data->expander->tail->type = current->type;
		}
		current = current->next;
	}
	// dll_print_forward(data->expander);
	check_node_null(data);
	return 0;
}
