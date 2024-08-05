/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:18:55 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 17:37:38 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**arr_dup(char **arr)
{
	int		i;
	int		j;
	int		len;
	char	**dup;

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
	return (dup);
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

static void	error_message(char *str)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

static void	determine_exit_code(char *str, t_data *data)
{
	int	nb;

	if (!str)
		g_exit_status = 0;
	else if (is_str_digit(str))
		g_exit_status = ft_atoi(str) % 256;
	else
	{
		nb = ft_atoi(str);
		if (nb < 0)
		{
			g_exit_status = (256 - (-nb)) % 256;
			exit(g_exit_status);
		}
		else if (nb > 0)
		{
			g_exit_status = nb % 256;
			exit(g_exit_status);
		}
		error_message(str);
		g_exit_status = 255;
	}
	free_var("%cmd %lst", data->parser, data->env);
	free_str(str);
	exit(g_exit_status);
}

int	__exit(t_data *data, t_cmd *simple_cmd)
{
	char	*tmp;

	tmp = NULL;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (simple_cmd->str[1] && simple_cmd->str[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_exit_status = 1;
		return (EXIT_FAILURE);
	}
	if (simple_cmd->str[1])
		tmp = ft_strdup(simple_cmd->str[1]);
	free(simple_cmd->str);
	simple_cmd->str = NULL;
	free_str(data->input);
	determine_exit_code(tmp, data);
	return (EXIT_SUCCESS);
}
