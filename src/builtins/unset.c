# include "../../inc/minishell.h"

void    del_node(t_list **node, char *str)
{
    t_list  *temp;
    t_list  *prev;

    temp = *node;
    prev = NULL;
    if (temp && ft_strncmp(temp->content, str, ft_strlen(str) == 0))
    {
        *node = temp->next;
        free(temp);
        return ;
    }
    while (temp->next && ft_strncmp(temp->content, str, ft_strlen(str) != 0))
    {
        prev = temp;
        temp = temp->next;
    }
    prev->next = temp->next;
    free(temp);
}

void    unset(t_list **env, t_list **export, char *var)
{
    del_node(env, var);
    del_node(export, var);
}

int main(int argc, char **argv, char **envp)
{
    t_list *env = init_env(envp);
    t_list *export = init_export(env);
    // export_node(&env, &export, "JOJOLAFRITE=123");
    // print_export(export);
    // sleep(2);
    unset(&env, &export, "var");
    print_export(export);
    return (0);
}