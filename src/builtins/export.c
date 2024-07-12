#include "../../inc/minishell.h"

/// A REFAIRE

void	print_export(t_lst *env)    //besoin de check le triage par ordre ascii et ne pas trier les valeur export
{
	t_env *node;
	char *join;

	node = env->head;
	while (node)
	{
		join = ft_strjoin(node->var, "=");
		join = ft_strjoin(join, node->value);
		// printf("join : %s\n", join);
		if (ft_strncmp("_=/Users/vdarras/Cursus/minishell/./minishell", node->var, 46) != 0)
		{
			ft_printf("declare -x ");
			ft_printf("%s", node->var);
			if (node->value)
				ft_printf("=\"%s\"\n", node->value);
			else
				write(1, "\n", 1);
		}
		free(join);
		node = node->next;
	}
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
	{
		printf("check 3\n");
		return_value = export_var(data, str);
	}
	else if (str[j] && str[j] == '=')
		printf("var=\n"); //replace by function
	else if (str[j] && str[j + 1] && str[j + 1] == '=' && str[j] == '+')
		printf("var+=\n"); //replace by function
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
	printf("check \n");
	while (arr[i])
	{
		j = 0;
		str = arr[i];
		while (str[j] && (ft_isalnum((int)str[j]) == 1 || str[j] == '_'))
			j++;
		printf("check 1\n");
		return_value = dispatch_export(data, str, j);
		printf("check 2\n");
		i++;
	}
	return return_value;
}

//TODO : REPLACE IF ALREADY EXISTING VAR ; VAR+=XXXX -> ft_strjoin

//export sans rien a check
//export avec une variable sans = a check

//a faire export += et export multi variabbles et export var="string"

//pour export tout seul mettre la liste dans dans un char** et faire une bubble sort