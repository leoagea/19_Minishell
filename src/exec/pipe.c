#include "../../inc/minishell.h"

void    exec_pipe(t_cmd *command)
{
    int     pipe_fd[2];
    int     fd_in;
    pid_t     pid;
    t_cmd   *node;

    node = command;
    fd_in = STDIN_FILENO;
    while (node)
    {
        if (node->next)  // si commande apres -> pipe
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("pipe");
                exit(1);
            }
        }

        pid = fork();    // child process pour executer commande
        if (pid == -1)
        {
            perror("fork");
            exit (1);
        }
        if (pid == 0)
        {
            if (fd_in != STDIN_FILENO)
            {
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }
            if (node->next)     // si commande apres -> j'ecris sur le pipe 
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
                close(pipe_fd[0]);
            }
            // redirections(node);   // ouvre fichier puis redirige entree ou sortie depuis ou vers le fd
            if (/*execute_builtin(node)*/-1 == -1)
            {
                printf("%s\n",node->str[0]);
                execve(node->str[0], node->str, command->env);
                perror("execve");
                exit (1);
            }
            exit (0);
        }
        else 
        {
            wait(NULL);
            if (fd_in != STDIN_FILENO)
                close(fd_in);
            if (node->next)
            {
                close(pipe_fd[1]);
                fd_in = pipe_fd[0];
            }
        }
        node = node->next;
    }
}

