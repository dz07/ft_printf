/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdiab- <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:35:45 by zdiab-            #+#    #+#             */
/*   Updated: 2018/11/29 15:55:35 by zdiab-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int			ft_printf(const char *format, ...);
char		**classified(char *str, va_list args, char **ptr);
int			ft_strdoub(double b);
char		**sort_args(char *str);
int			flag(char *str, int i, char **ptr, int *j);
int			catch(char *str, char **ptr);
char		*ft_itob(unsigned long long nbr, char *base);
int			ft_atoi(const char *str);
void		ft_putchar(char c);
void		ft_putstr(const char *str);
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_atoi_base(char *str, char *base);
char		*ft_itoa_base(int value, char *base);
void		*ft_memalloc(size_t size);
void		ft_bzero(void *b, size_t n);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strdup(const char *src);
int			ft_isupper(int c);
char        *ft_itoa(long long int nbr);



#endif
