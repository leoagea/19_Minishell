#include "../../inc/minishell.h"

char    *path(char *command)
{
    char    **dir_command;
    char    *temp;
    char    *final_path;
    int     i;

    i = -1;
    dir_command = ft_split("/Users/vdarras/homebrew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki", ':');
    if (!dir_command)
        exit(1);
    i = -1;
    while(dir_command[++i])
    {
        temp = ft_strjoin("/", command);
        if (!temp)
            exit(1);
        final_path = ft_strjoin(dir_command[i], temp);
        if(!final_path)
            exit(1);
        free(temp);
        if (access(final_path, F_OK) == 0)
            return (free_tab_char(dir_command), final_path);
        free(final_path);
    }
    return (free_tab_char(dir_command), NULL);
}

void    absolute_path(t_cmd *command)
{
    t_cmd   *node;
    char    *final_path;
    char    *temp;
    node = command;
    while (node)
    {
        if (access(node->str[0], F_OK) != 0)
        {
            if (path(node->str[0]) != NULL)
                node->absolute_path = path(node->str[0]);
        }
        node = node->next;
    }
}

void    exec_pipe(t_cmd *command)
{
    int     pipe_fd[2];
    int     wstatus;
    int     fd_in;
    pid_t     pid;
    t_cmd   *node;

    node = command;
    fd_in = STDIN_FILENO;

    // absolute_path(node);
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
            redirections(node);   // ouvre fichier puis redirige entree ou sortie depuis ou vers le fd       
            if (node->next)     // si commande apres -> j'ecris sur le pipe 
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
                close(pipe_fd[0]);
            }
            if (/*execute_builtin(node)*/-1 == -1)
            {
                printf("--> %s\n", node->str[0]);
                execve(node->str[0], node->str, command->env);
                perror("execve");
                exit (1);
            }
            exit (0);
        }
        else 
        {
            wait(&wstatus);
            if (WIFEXITED(wstatus))
            {
                int statusCode = WEXITSTATUS(wstatus);
                printf("EXIT STATUS %d\n", statusCode);
            }
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

