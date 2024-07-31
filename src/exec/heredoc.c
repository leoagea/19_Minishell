/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdarras <vdarras@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:42:48 by lagea             #+#    #+#             */
/*   Updated: 2024/07/31 20:44:49 by vdarras          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_heredoc(t_cmd *command)
{
	t_node	*node;
	t_cmd	*temp;
	int		i;

	i = 1;
	temp = command;
	while (temp)
	{
		node = temp->redirections->head;
		while (node)
		{
			if (node->type == HEREDOC)
				heredoc(node, i);
			node = node->next;
		}
		i++;
		temp = temp->next;
	}
}

void	heredoc(t_node *node, int i)
{
	int		fd;
	char	*line;
	char	*file;
	char	*itoa;

	itoa = ft_itoa(i);
	file = ft_strjoin("/tmp/.tmp_heredoc", itoa);
	line = "";
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("open");
		exit (1);
	}
	heredoc_loop(fd, line, node);
	free(itoa);
	free_str(file);
	close(fd);
}

void	heredoc_loop(int fd, char *line, t_node *node)
{
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (line == NULL)
		{
			ft_putstr_fd(line, fd);
			break ;
		}
		if (ft_strncmp(line, node->str, ft_strlen(line) - 1)
			== 0 && *line != '\n')
		{
			free_str(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free_str(line);
	}
}

void	unlink_tmp(void)
{
	char	*file;
	char	*itoa;
	int		i;

	i = 1;
	itoa = ft_itoa(i);
	file = ft_strjoin("/tmp/.tmp_heredoc", itoa);
	free_str(itoa);
	while (unlink(file) == 0)
	{
		i++;
		itoa = ft_itoa(i);
		free(file);
		file = ft_strjoin("/tmp/.tmp_heredoc", itoa);
		free_str(itoa);
	}
	free_str(file);
}
