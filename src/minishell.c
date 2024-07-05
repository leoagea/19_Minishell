/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/07/05 20:38:28 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *line;

	t_list *env;
	t_list *export;

	env = init_env(envp);
	export = init_export(env);
	while (1)
	{
		// handle_signal();
		// line = readline("\001\e[0;31m\002> minishell$ \001\e[0m\002");
		// if (line == NULL)
		// {
		// 	// write(1, "\33[2K\r", 6);
		// 	// write(1, "\001\e[0;31m\002> minishell$ \001\e[0m\002exit\n", 33);
		// 	write(1, "exit\n", 5);
		// 	exit (0);
		// }
		// if (line[0] != '\0')
        // 	add_history(line);
		// if (command->is_builtin == 0)
		// 	execute_builtin(command);   // TODO
		
		exec_pipe(command);
		break;
		// free_command(command); // TODO
	}
	free (line);
	return (0);
}