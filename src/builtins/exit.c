/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:18:55 by lagea             #+#    #+#             */
/*   Updated: 2024/07/18 17:24:11 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char **arr_dup(char **arr)
{
	int i;
	int j;
	int len;
	char **dup;

	i = 0;
	while (arr[i])
		i++;
	dup = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (arr[i])
	{
		len = ft_strlen(arr[i]);
		dup[i] = malloc(sizeof(char) * len + 1);
		dup[i] = ft_strdup(arr[i]);
		i++;
	}
	dup[i] = NULL;
	return dup;
}

int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	determine_exit_code(char **str)
{
	if (!str[1])
		g_exit_status = 0;
	else if (is_str_digit(str[1]))
		g_exit_status = ft_atoi(str[1]);
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		g_exit_status = 255;
	}
	free_var("%arr", str);
	exit(g_exit_status);
}

int	ft_exit(t_data *data, t_cmd *simple_cmd)
{
	char	**str;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (simple_cmd->str[1] && simple_cmd->str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	str = arr_dup(simple_cmd->str);;
	// free_var("%dll %dll %cmd %lst %exp", data->lexer, data->expander, data->parser, data->env, data->env_expand);
	// free_dll(data->lexer);
	// free_dll(data->expander);
	// free_cmd(data->parser);
	// free_lst(data->env);
	// free_exp(data->env_expand);
	determine_exit_code(str);
	free_arr(str);
	return (EXIT_SUCCESS);
}
