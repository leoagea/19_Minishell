/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:48:26 by lagea             #+#    #+#             */
/*   Updated: 2024/07/30 18:45:04 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_str(char *str)
{
	if (!str)
		return ;
	free(str);
	str = NULL;
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free_str(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_lst(t_lst *lst)
{
	t_env	*tmp;
	t_env	*node;

	if (!lst)
		return ;
	node = lst->head;
	while (node)
	{
		tmp = node;
		node = node->next;
		free_str(tmp->var);
		free_str(tmp->value);
		free(tmp);
		tmp = NULL;
	}
	free(lst);
	lst = NULL;
}

static int	dispatch_free(const char *s, va_list *arg)
{
	if (!(*s + 1))
		return (0);
	else if (*(s + 1) == 's' && *(s + 2) == 't' && *(s + 3) == 'r')
		return (free_str(va_arg(*arg, char *)), 1);
	else if (*(s + 1) == 'd' && *(s + 2) == 'l' && *(s + 3) == 'l')
		return (free_dll(va_arg(*arg, t_dll *)), 1);
	else if (*(s + 1) == 'c' && *(s + 2) == 'm' && *(s + 3) == 'd')
		return (free_cmd(va_arg(*arg, t_dll_cmd *)), 1);
	else if (*(s + 1) == 'e' && *(s + 2) == 'x' && *(s + 3) == 'p')
		return (free_exp(va_arg(*arg, t_env_expand *)), 1);
	else if (*(s + 1) == 'l' && *(s + 2) == 's' && *(s + 3) == 't')
		return (free_lst(va_arg(*arg, t_lst *)), 1);
	else if (*(s + 1) == 'a' && *(s + 2) == 'r' && *(s + 3) == 'r')
		return (free_arr(va_arg(*arg, char **)), 1);
	else
		return (0);
}

/*  str = char*
	dll = dll
	cmd = dll_cmd
	exp = env_expand
	lst = lst
	arr = char**
*/
int	free_var(const char *s, ...)
{
	int		temp;
	int		index;
	va_list	arg;

	temp = 0;
	index = 0;
	va_start(arg, s);
	while (*s)
	{
		if (*s == '%' && dispatch_free(s, &arg))
			s += 3;
		else
			s++;
	}
	va_end(arg);
	return (0);
}
