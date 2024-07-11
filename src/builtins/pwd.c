#include "../../inc/minishell.h"

char *get_pwd(void)
{
    int i;
    int len;
    char *pwd;
    char buffer[BUFFER_SIZE];

    if (!getcwd(buffer, BUFFER_SIZE))
        return (NULL);
    len = ft_strlen(buffer);
    pwd = malloc(sizeof(char) * len + 1);
    if (!pwd)
        return NULL;
    i = -1;
    while(buffer[i])
        pwd[i] = buffer[i];
    return (pwd);
}

int pwd(void)
{
    char buffer[BUFFER_SIZE];

    if (!getcwd(buffer, BUFFER_SIZE))
    {
        ft_putstr_fd("Error :", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putchar_fd('\n', 2);
        return (1);
    }
    ft_putstr_fd(buffer, 1);
    ft_putchar_fd('\n', 1);
    return (0);
}

// int main(void)
// {
//     pwd();
//     return (0);
// }