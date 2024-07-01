# include "../../inc/minishell.h"

void    del_node(t_list **node, char *str)
{
    t_list  *temp;
    t_list  *prev;
    int     len;

    temp = *node;
    prev = NULL;
    len = ft_strlen(str);
    if (temp && ft_strncmp(temp->content, str, len) == 0 && *((char *)temp->content + len + 1 ) == '=')
    {
        *node = temp->next;
        temp->next = NULL;
        free(temp);
        return ;
    }
    while (temp && ft_strncmp(temp->content, str, len) != 0 && *((char *)temp->content + len + 1 ) != '=')
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return ;
    prev->next = temp->next;
    free (temp);
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
    export_node_0equal(&export, "VICENTE");
    // print_export(export);
    print_export(export);
    unset(&env, &export, "VICENTE");
    sleep(1);
    printf("\n\n");
    print_export(export);
    return (0);
}