/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:18:55 by lagea             #+#    #+#             */
/*   Updated: 2024/07/31 20:19:51 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static char **arr_dup(char **arr)
// {
// 	int i;
// 	int len;
// 	char **dup;

// 	i = 0;
// 	while (arr[i])
// 		i++;
// 	dup = malloc(sizeof(char *) * i + 1);
// 	i = 0;
// 	while (arr[i])
// 	{
// 		len = ft_strlen(arr[i]);
// 		dup[i] = malloc(sizeof(char) * len + 1);
// 		dup[i] = ft_strdup(arr[i]);
// 		i++;
// 	}
// 	dup[i] = NULL;
// 	return (dup);
// }

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

static void	determine_exit_code(char *str, t_data *data)
{
	if (!str)
		g_exit_status = 0;
	else if (is_str_digit(str))
		g_exit_status = ft_atoi(str);
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		g_exit_status = 255;
	}
	free_var("%cmd %lst", data->parser, data->env);
	// free_arr(str);
	free_str(str);
	// system("leaks minishell");
	exit(g_exit_status);
}

int	__exit(t_data *data, t_cmd *simple_cmd)
{
	char *tmp = NULL;
	
	ft_putendl_fd("exit", STDERR_FILENO);
	if (simple_cmd->str[1] && simple_cmd->str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	// str = arr_dup(simple_cmd->str);
	if (simple_cmd->str[1])
		tmp = ft_strdup(simple_cmd->str[1]);
	// free_var("%dll %dll %cmd %lst %exp", data->lexer, data->expander, data->parser, data->env, data->env_expand);
	// free_dll(data->lexer);
	// free_dll(data->expander);
	// free_cmd(data->parser);
	// free_lst(data->env);
	// free_exp(data->env_expand);
	free(simple_cmd->str);
	simple_cmd->str = NULL;
	free_str(data->input);
	determine_exit_code(tmp, data);
	return (EXIT_SUCCESS);
}
