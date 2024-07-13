#include "../../inc/minishell.h"

/// A REFAIRE
void swap_node(t_env *a, t_env *b, t_lst *exp)
{
	t_env *tmp;
	tmp = a;
	a = b;
	b = tmp;
	if (a == exp->head)
		exp->head = b;
	else if (b == exp->head)
		exp->head = a;
}

static t_lst *put_in_lst_export(t_lst *env)
{
	t_lst *export;
	t_env *new;
	t_env *current;

	export = lst_init();
	if (!export)
		return NULL;
	current = env->head;
	while (current != NULL)
	{
		new = lst_new(current->var, current->value, 1);
		if (!new)
			return NULL;
		lst_insert_tail(new, export);
		current = current->next;
	}
	current = export->head;
	return export;
}

void	print_export(t_lst *env)    //besoin de check le triage par ordre ascii
{
	int i = 0;
	char *join;
	t_env *node;
	t_lst *export;

	export = put_in_lst_export(env);
	sort_export(export);
	// node = export->head;
	// printf("check\n\n");
	// while (node)
	// {
	// 	join = ft_strjoin(node->var, "=");
	// 	join = ft_strjoin(join, node->value);
	// 	// if (ft_strncmp("_=/Users/vdarras/Cursus/minishell/./minishell", node->var, 46) != 0)
	// 	// {
	// 	// 	ft_printf("declare -x ");
	// 	// 	ft_printf("%s", node->var);
	// 	// 	if (node->value)
	// 	// 		ft_printf("=\"%s\"\n", node->value);
	// 	// 	else
	// 	// 		write(1, "\n", 1);
	// 	// }
	// 	printf("%s\n", join);
	// 	free(join);
	// 	node = node->next;
	// }
}


static int dispatch_export(t_data *data, char *str, int j)
{
	int return_value;

	return_value = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		return_value = 1;
		ft_printf("bash: export: `%s': not a valid identifier\n", str);
	}
	else if (str[j] == '\0')
		return_value = export_var(data, str);
	else if (str[j] && str[j] == '=')
		return_value = export_var_value(data, str);
	else if (str[j] && str[j + 1] && str[j + 1] == '=' && str[j] == '+')
		return_value = export_cat_value(data, str);
	else
	{
		return_value = 1;
		ft_printf("bash: export: `%s': not a valid identifier\n", str);
	}
	return return_value;
}

int export(t_data *data, t_cmd *cmd)
{
	int i;
	int j;
	int return_value;
	char **arr;
	char *str;

	i = 1;
	arr = cmd->str;
	return_value = 0;
	if (!arr[1])
		print_export(data->env);
	while (arr[i])
	{
		j = 0;
		str = arr[i];
		while (str[j] && (ft_isalnum((int)str[j]) == 1 || str[j] == '_'))
			j++;
		return_value = dispatch_export(data, str, j);
		i++;
	}
	return return_value;
}

//export sans rien a check

//pour export tout seul mettre la liste dans dans un char** et faire une bubble sort