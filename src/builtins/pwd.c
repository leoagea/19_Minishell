#include "../../inc/minishell.h"

char *get_pwd(void)
{
    char buffer[BUFFER_SIZE];

    if (!getcwd(buffer, BUFFER_SIZE))
        return (NULL);
    return (buffer);
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