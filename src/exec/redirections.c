#include "../../inc/minishell.h"

void    handle_redirections(t_cmd *command)
{
    int         fd;
    t_dll       *node;

    node = command->redirections;
    if (command->redirections == NULL)
        return ;
    if (node->head->type == INPUT)
    {
        fd = open(command->redirections->head->str, O_RDONLY, 0777);
        if (fd == -1)
        {
            perror("open");
            exit (1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    if (node->head->type == TRUNC)
    {
        fd = open(command->redirections->head->str, O_WRONLY | O_CREAT | O_TRUNC, 777);
        if (fd == -1)
        {
            perror("open");
            exit (1);
        }
        dup2(fd, STDOUT_FILENO);
        close (fd);
    }
    if (node->head->type == APPEND)
    {
        fd = open(command->redirections->head->str, O_WRONLY | O_CREAT | O_APPEND, 777);
        if (fd == -1)
        {
            perror("open");
            exit (1);
        }
        dup2(fd, STDOUT_FILENO);
        close (fd);
    }
    // if (node->head->type == HEREDOC)
    // {
    //     fd = open(command->redirections->head->str, O_WRONLY | O_CREAT, 777);
    //     if (fd == -1)
    //     {
    //         perror("open");
    //         exit (1);
    //     }
    //     dup2(fd, STDOUT_FILENO);
    //     close (fd);
    // }
}

