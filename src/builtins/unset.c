# include "../../inc/minishell.h"

static void lst_delete_node(t_env *prev, t_env *delete, t_lst *lst)  
{  
    t_env *node;  
	 
    node = delete;
    if (!prev)
        lst->head = node->next;
    else if (node == lst->tail)
        lst->tail = prev;
    else
        prev->next = node->next;  
	free(node);
}

void    unset(t_lst *env, char *var)
{
    t_env *node;

    node = env->head;
    if (ft_strncmp(node->var, env->head->var, INT_MAX) != 0)
    {
        printf("env var to delete : %s\n", var);
        printf("node->var->head var : %s\n", node->var);
        lst_delete_node(NULL, node, env);
        printf("check\n");
        return ;
    }
    while(node)
    {
        if (ft_strncmp(node->next->var, var, INT_MAX) == 0)
        {
            lst_delete_node(node, node->next, env);
            printf("check 1\n");
            return ;
        }
        node = node->next;
    }
}
