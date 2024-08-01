/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/08/01 20:52:31 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	t_cmd	*command;

	check_arg(argc, argv);
	data.env = init_env(envp);
	if (init_shlvl(&data))
		return (1);
	handle_signal();
	while (1)
	{
		if (input_loop(line, &data, command) == 1)
			continue ;
	}
	return (0);
}
