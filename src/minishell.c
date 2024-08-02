/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 14:11:33 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	t_cmd	*command;

	g_exit_status = 0;
	check_arg(argc, argv);
	data.env = init_env(envp);
	if (init_shlvl(&data))
		return (1);
	while (1)
	{
		handle_signal(0);
		if (input_loop(line, &data, command) == 1)
			continue ;
	}
	return (0);
}

//verif cd 