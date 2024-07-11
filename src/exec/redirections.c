#include "../../inc/minishell.h"

void    redirections(t_cmd *command)
{
    int         fd;
    t_node       *node;

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
        node = node->next;
    }
    // if (node->type == HEREDOC)
    //     heredoc(t_cmd *command);
        // fd = open(command->redirections->head->str, O_WRONLY | O_CREAT, 777);
        // if (fd == -1)
        // {
        //     perror("open");
        //     exit (1);
        // }
        // dup2(fd, STDOUT_FILENO);
        // close (fd);
}

