/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:55:10 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 13:05:19 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <unistd.h>

/*---------------------------------PARSE---------------------------------*/

int	ft_check_next_char(const char *s, int index);
int	ft_parse_printf(const char *s, int index, va_list *par);

/*----------------------------PRINT_ELEMENTS-----------------------------*/

int	ft_print_char(char c);
int	ft_print_string(char *s);
int	ft_print_decimal(int n);
int	ft_print_udecimal(unsigned int n);
int	ft_print_hex(unsigned int n, char *base);

/*---------------------------PRINT_ELEMENTS_2----------------------------*/

int	ft_print_hex_add(unsigned long n);
int	ft_print_add(unsigned long add);

/*-------------------------------UTILS_LEN--------------------------------*/

int	ft_int_len(long n);
int	ft_add_len(unsigned long add);
int	ft_hex_len(unsigned int hex);

#endif