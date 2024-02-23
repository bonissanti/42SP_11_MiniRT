/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:57:20 by brunrodr          #+#    #+#             */
/*   Updated: 2023/05/19 12:20:24 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50

# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_flags
{
	unsigned int	hashtag;
	unsigned int	plus;
	unsigned int	space;
}					t_flags;

// Part 1 - Libc functions
// ----------------- Memory functions -----------------

void				ft_bzero(void *s, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memchr(const void *str, int chr, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_calloc(size_t num, size_t size);

// ----------------- String functions -----------------

int					ft_isprint(int c);
int					ft_atoi(const char *str);
int					ft_isalnum(int c);
int					ft_isalpha(int i);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isspace(char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

// Part 2 - Additional functions
// ----------------- String functions -----------------

char				*ft_itoa(int n);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strtrim(const char *s1, const char *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_split(char const *s, char c);
char				**ft_split_space(char const *s);

// ------------------- FD functions -------------------

int					ft_putchar_fd(char c, int fd);
int					ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_putstr_fd(const char *s, int fd);

// Bonus part
// ----------------- Linked list -----------------

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

// ----------------- GET_NEXT_LINE -----------------

char				*get_next_line(int fd);
char				*gnl_strjoin(char *s1, char *s2);
size_t				gnl_strlen(char *s);

// ----------------- FT_PRINTF --------------------

int					ft_printf(const char *str, ...);

//####################### Specifiers #######################

int					print_base(int arg, int base);
int					print_char(int arg);
int					print_int(int arg, t_flags flags);
int					print_percent(void);
int					print_pointer(unsigned long int arg, int base);
int					print_string(char *arg);
int					print_unsign_int(unsigned int arg);
int					print_hex_d(unsigned int arg, int uppercase, t_flags flags);

//####################### Utils #######################

int					putnbr_ptr(unsigned long int value, int base);
int					putnbr_hex(unsigned int value, int base, int uppercase);
int					putnbr_int(int value, int base);
int					ft_putchar(char c);
int					get_specifier_length(const char *format);
int					check_uppercase(const char format);
void				active_flags(const char **format, t_flags *flags);

#endif
