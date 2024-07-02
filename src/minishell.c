/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:09:13 by lagea             #+#    #+#             */
/*   Updated: 2024/07/02 18:21:00 by vdarras          ###   ########.fr       */
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
		handle_signal();
		line = readline("\001\e[0;31m\002minishell$ \001\e[0m\002");
		if (line == NULL)
		{
			write(1, "\33[2K\r", 6);
			write(1, "\001\e[0;31m\002minishell$ \001\e[0m\002exit\n", 32);
			exit (0);
		}
		if (line[0] != '\0')
        	add_history(line);
		if (ft_strncmp(line, "export", INT_MAX) == 0)
			print_export(export);
		else if (ft_strncmp(line, "env", INT_MAX) == 0)
			print_env(env);
		else if (ft_strncmp(line, "pwd", INT_MAX) == 0)
			pwd();
		else if (ft_strncmp(line, "cd", INT_MAX) == 0)
			cd_home(&env, &export);
		else if (ft_strncmp(line, "exit", INT_MAX) == 0)
			exit(1);
	}
	return (0);
}