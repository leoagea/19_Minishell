/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:17:19 by vdarras           #+#    #+#             */
/*   Updated: 2024/08/05 15:49:35 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	no_access(char *command)
{
	struct stat	data;

	if (stat(command, &data) == -1)
	{
		perror("stat");
		exit(1);
	}
	if ((data.st_mode & S_IFMT) == S_IFDIR)
	{
		write(2, "bash: ", 6);
		write(2, command, ft_strlen(command));
		write(2, ": is a directory\n", ft_strlen(": is a directory\n"));
		exit(126);
	}
}

void	command_not_found(char *command)
{
	write(2, "bash: ", 6);
	write(2, command, ft_strlen(command));
	write(2, ": command not found\n", ft_strlen(": command not found\n"));
	exit(127);
}

void	error_management(char *command)
{
	if ((ft_strncmp(command, "./", 2) == 0))
	{
		if (errno == EACCES)
			no_access(ft_strchr(command, '/') + 1);
		else
		{
			write(2, "bash: ", 6);
			write(2, command, ft_strlen(command));
			write(2, ": No such file or directory\n",
				ft_strlen(": No such file or directory\n"));
			exit(127);
		}
	}
	command_not_found(command);
}
