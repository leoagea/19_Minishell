/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 01:26:11 by lagea             #+#    #+#             */
/*   Updated: 2024/08/02 13:08:16 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <errno.h> //errno
# include <fcntl.h> //open
# include <limits.h>
# include <math.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h> //strerror
# include <unistd.h>

# define BUFFER_SIZE 10000
/*--------------------------------LIBFT----------------------------------*/
/*Libc functions*/
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_atoi(const char *str);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strnstr(const char *str, const char *to_find,
						size_t len);

void				ft_bzero(void *str, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memset(void *str, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);

size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);

/*Fonctions additionnelles*/

char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/*Partie bonus*/

typedef struct s_list
{
	void			*var;
	void			*value;
	int				flag;
	int				count;
	int				total;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *var, void *value, int flag);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

int					ft_lstsize(t_list *lst);

void				ft_lstadd_front(t_list **lst, t_list *_new);
void				ft_lstadd_back(t_list **lst, t_list *_new);
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));

/*--------------------------------PRINTF---------------------------------*/

int					ft_printf(const char *s, ...);

/*----------------------------ADDED FUNCTIONS----------------------------*/

void				ft_putunbr_fd(unsigned int n, int fd);
long				ft_atol(const char *str);
int					ft_atoi_base(char *str, char *base);
char				*ft_realloc(char *ptr, size_t new_size);

/*-------------------------DOUBLE LIMKED LIST----------------------------*/

typedef enum e_type
{
	INPUT = 1,
	TRUNC,
	HEREDOC,
	APPEND,
	PIPE,
	CMD,
	OPTION,
	ARG
}					t_type;

typedef struct s_node
{
	char			*str;
	t_type			type;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct s_dll
{
	struct s_node	*head;
	struct s_node	*tail;
}					t_dll;

int					dll_size(t_dll *dll);
void				dll_insert_head(char *data, t_dll *dll);
void				dll_insert_tail(char *data, t_dll *dll);
void				dll_delete_head(t_dll *dll);
void				dll_delete_tail(t_dll *dll);
void				dll_print_backward(t_dll *dll);
void				dll_print_forward(t_dll *dll);
void				dll_clear(t_dll *dll);
t_node				*dll_new_node(char *input);

/*-----------------------------GET NEXT LINE---------------------------------*/

char				*get_next_line(int fd);

#endif
