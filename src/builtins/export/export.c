/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:40:35 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 13:01:13 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static const char	**put_int_arr(t_lst *env)
{
	const int	size = lst_size(env);
	char		**arr;
	int			i;
	t_env		*node;
	int			len;

	i = 0;
	arr = malloc(sizeof(char *) * size + 1);
	node = env->head;
	while (node)
	{
		len = ft_strlen(node->var);
		arr[i] = ft_strdup(node->var);
		i++;
		node = node->next;
	}
	arr[i] = NULL;
	return ((const char **)arr);
}

static void	print_export(t_lst *env)
{
	const char	**arr = put_int_arr(env);
	int			i;
	t_env		*node;

	sort_export((char **)arr, lst_size(env));
	i = -1;
	while (arr[++i])
	{
		if (ft_strncmp(arr[i], "_", INT_MAX) == 0)
		{
			i++;
			continue ;
		}
		node = env->head;
		while (arr[i] && node->var && ft_strncmp(arr[i], node->var,
				INT_MAX) != 0)
			node = node->next;
		if (node->flag != 2)
			ft_printf("declare -x %s", arr[i]);
		if (node->value && (node->flag == 1 || node->flag == 0))
			ft_printf("=\"%s\"\n", node->value);
		if (!node->value)
			write(1, "\n", 1);
	}
	free_arr((char **)arr);
}

static int	dispatch_export(t_data *data, char *str, int j)
{
	int	return_value;

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
	return (return_value);
}

void	_export(t_data *data, t_cmd *cmd)
{
	int		i;
	int		j;
	int		return_value;
	char	**arr;
	char	*str;

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
	g_exit_status = return_value;
}
