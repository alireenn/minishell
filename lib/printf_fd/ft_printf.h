/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcucino <gcucino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:50:04 by gcucino           #+#    #+#             */
/*   Updated: 2022/07/14 18:39:58 by gcucino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int				ft_printf(int fd, const char *format, ...);
int				ft_get_arg(int fd, va_list *args, char *str, int *i);

//MANDATORY
int				ft_printuns(int fd, unsigned int n);
int				ft_print_ex(int fd, unsigned int n, int flag);
int				ft_putnbr(int fd, unsigned int n);
int				ft_printnbr(int fd, int n);
int				ft_print_ptr(int fd, void *ptr);
int				ft_printp(int fd, unsigned long long n, int flag);

//TOA
char			*ft_ctoa(char c);
char			*ft_itoa(int n);
int				get_size(int n);
char			*ft_ptoa(void *p);
char			*ft_utoa(unsigned int n);
char			*ft_xtoa(unsigned int n, int flag);

//UTILS
int				ft_printchar(int fd, int c);
int				ft_printstr(int fd, char *str);
void			*ft_memset(void *b, int c, size_t len);
int				ft_char_in_set(char c, const char *set);
char			ft_convert_ex(int n, int nc);
char			*ft_strcpy(char *str);
size_t			ft_strlen(const char *s);
char			*ft_strjoin_width(char *s2, int width, int minus, int zero);
char			*ft_strjoin_width_sign(char *s, int width, int minus, int zero);
char			*ft_strjoin(char const *s1, char *s2);
int				ft_print_str(char *str);
int				ft_atoi(const char *str);
unsigned int	ft_atou(const char *str);

#endif