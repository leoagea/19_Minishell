/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 00:19:00 by lagea            ###   ########.fr       */
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

//env -i ./minishell probleme free abort

//verif cd 