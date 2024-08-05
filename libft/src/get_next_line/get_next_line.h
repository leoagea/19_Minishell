/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:51:42 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 13:04:59 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*-------------------------GET_NEXT_LINE_UTILS---------------------------*/

int		my_strlen(const char *str);
char	*strchr_index(char *str);
char	*strjoin(char *s1, char *s2);
char	*my_strdup(char *s1);
char	*substr(char *s, int start, int len);

#endif