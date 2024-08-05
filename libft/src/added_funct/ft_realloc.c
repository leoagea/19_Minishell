/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:44:42 by lagea             #+#    #+#             */
/*   Updated: 2024/07/30 18:03:44 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/libft.h"

char	*ft_realloc(char *ptr, size_t new_size)
{
	char	*new_ptr;
	size_t	old_size;

	if (ptr == NULL)
		return (malloc(new_size * sizeof(char)));
	if (new_size == 0)
	{
		free(ptr);
		ptr = NULL;
		return (NULL);
	}
	new_ptr = malloc(new_size * sizeof(char));
	if (new_ptr == NULL)
		return (NULL);
	old_size = ft_strlen(ptr);
	if (old_size < new_size)
		ft_memcpy(new_ptr, ptr, old_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}
