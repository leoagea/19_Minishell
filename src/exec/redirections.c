#include "../../inc/minishell.h"

void    redirections(t_cmd *command)
{
    int         fd;
    int         temp_fd;
    t_node       *node;
    int         i = 0;

    node = command->redirections->head;
    while (node != NULL)
    {
        if (node->type == INPUT)
        {
            fd = open(node->str, O_RDONLY, 0777);
            if (fd == -1)
            {
                perror("open");
                exit (1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        if (node->type == TRUNC)
        {
            fd = open(node->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
            if (fd == -1)
            {
                perror("open");
                exit (1);
            }
            dup2(fd, STDOUT_FILENO);
            close (fd);
        }
        if (node->type == APPEND)
        {
            fd = open(node->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
            if (fd == -1)
            {
                perror("open");
                exit (1);
            }
            dup2(fd, STDOUT_FILENO);
            close (fd);
        }
        if (node->type == HEREDOC)
        {
            i = 1;
            heredoc(node);
        }    
        node = node->next;
    }
    if (i == 1)
    {
        fd = open("/tmp/.tmp_heredoc", O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
}

