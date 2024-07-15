#include "../../inc/minishell.h"

void	heredoc(t_node *node)
{
	int fd;
	int stdin_fd;
	char *line;

	line = "";
	fd = open("/tmp/.tmp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
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
	free(line);
	close(fd);
}