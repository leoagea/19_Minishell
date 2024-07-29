/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:42:48 by lagea             #+#    #+#             */
/*   Updated: 2024/07/29 13:03:16 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	init_heredoc(t_cmd *command)
{
	t_node	*node;
	t_cmd *temp;
	int i;

	i = 1;
	temp = command;
	while (temp)
	{
		node = temp->redirections->head;
		while (node)
		{
			if (node->type == HEREDOC)
        	{
            	heredoc(node, i);
        	}
			node = node->next;
		}
		i++;
		temp = temp->next;
	}
}

void	heredoc(t_node *node, int i)
{
	int fd;
	int stdin_fd;
	char *line;
	char *file;
	char *itoa;

	itoa = ft_itoa(i);
	file = ft_strjoin("/tmp/.tmp_heredoc", itoa);
	line = "";
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("open");
		exit (1);
	}
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if(ft_strncmp(line, node->str, ft_strlen(line) - 1) == 0 && *line != '\n')
			break ;
		ft_putstr_fd(line, fd);
	}
	free_str(line);
	close(fd);
}
