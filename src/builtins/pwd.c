#include "../../inc/minishell.h"

char *get_pwd(void)
{
    int i;
    int len;
    char *pwd;
    char buffer[BUFFER_SIZE];

    pwd = getcwd(NULL, 0);
    if (!pwd)
        return NULL;
    // if (!(getcwd(buffer, BUFFER_SIZE)))
    //     return NULL;
    // len = ft_strlen(buffer);
    // pwd = malloc(sizeof(char) * len + 1);
    // printf("pwd : %s\n", pwd);
    // if (!pwd)
    //     return NULL;
    // i = -1;
    // while(buffer[i])
    //     pwd[i] = buffer[i];
    return (pwd);
}

int pwd(void)
{
    char *pwd;

    if (!getcwd(pwd, BUFFER_SIZE))
    {
        ft_putstr_fd("Error :", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putchar_fd('\n', 2);
        return (1);
    }
    ft_putstr_fd(pwd, 1);
    ft_putchar_fd('\n', 1);
    return (0);
}

// int main(void)
// {
//     pwd();
//     return (0);
// }