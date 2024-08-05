/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:02:06 by vdarras           #+#    #+#             */
/*   Updated: 2024/08/05 13:52:03 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirections(t_cmd *command)
{
	char	*file;
	char	*itoa;
	t_node	*node;
	int		i;

	i = 0;
	node = command->redirections->head;
	itoa = ft_itoa(command->num_cmd);
	file = ft_strjoin("/tmp/.tmp_heredoc", itoa);
	while (node != NULL)
	{
		if (node->type == INPUT)
			open_input(node);
		if (node->type == TRUNC)
			open_trunc(node);
		if (node->type == APPEND)
			open_append(node);
		if (node->type == HEREDOC)
			i = 1;
		node = node->next;
	}
	if (i == 1)
		open_hdc(file);
}

void	open_trunc(t_node *node)
{
	int	fd;

	fd = open(node->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_printf("bash: %s: ", node->str);
		perror("");
		exit (1);
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
}

void	open_append(t_node *node)
{
	int	fd;

	fd = open(node->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		ft_printf("bash: %s: ", node->str);
		perror("");
		exit (1);
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
}

void	open_input(t_node *node)
{
	int	fd;

	fd = open(node->str, O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_printf("bash: %s: ", node->str);
		perror("");
		exit (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	open_hdc(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
