/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdiab- <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 16:43:57 by zdiab-            #+#    #+#             */
/*   Updated: 2018/11/29 16:45:04 by zdiab-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"
#include <stdlib.h> 

int flag(char *str, int i, char **ptr, int *j);
char **sort_args(char *str);
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

static void	append(char *str, int index, char c)
{
	str[index] = c;
}

static int	checkbase(char *base)
{
	int i;
	int j;
	int leng;

	i = 0;
	leng = ft_strlen(base);
	while (i < leng)
	{
		j = i + 1;
		if (base[i] == '+' || base[i] == '-')
			return (0);
		while (j < leng)
		{
			if (base[i] == base[j++])
				return (0);
		}
		i++;
	}
	return (1);
}

static int	nbrsize(unsigned long long nbr, int base)
{
	long long			i;
	unsigned long long	count;

	i = 0;
	count = 1;
	if (nbr == 0)
		return (1);
	while (nbr % base != 0 || nbr / base != 0)
	{
		nbr /= base;
		i++;
	}
	return (i);
}

char		*ft_itob(unsigned long long nbr, char *base)
{
	unsigned long long	num;
	int					multip;
	int					index;
	int					i;
	char				*result;

	multip = ft_strlen(base);
	index = nbrsize(nbr, multip);
	result = ft_memalloc(index-- + 1);
	num = (unsigned long long)nbr;
	if (!checkbase(base))
		return (ft_strdup(""));
	if (num == 0)
		return (ft_strdup("0"));
	while (num != 0)
	{
		i = (num % multip);
		append(result, index--, base[i]);
		num /= multip;
	}
	return (result);
}
/////////debut////////////ptr
//                      //
//                      //
/////////////////////////
int catch(char *str, char **ptr)
{
	int i,j,cnt=0;
	char *s;

	i = 0;
	j = 0;
	s = (char*)malloc(100);
	while (str[i])
	{
		if(str[i] == '%')
		{
			i++;
			i = flag(str, i, ptr, &j);
			cnt = 0;	
			while (str[i] <= '9' && str[i] >= '0')
				s[cnt++] = str[i++];

			if (ft_atoi(s))
			{
				cnt =0;
				while((unsigned long)cnt < (ft_atoi(s)-ft_strlen(ptr[j])))
				{
					ft_putchar(' ');
					cnt++;
				}
				s = (char*)malloc(100);
			}

			if (str[i] == 'l' || str[i] == 'h')
				i++;
			if (str[i] == 'l' || str[i] == 'h')
				i++;
			if(str[i] == 'p')
				ft_putstr(ptr[j++]);
			else if(str[i] == 'c')
				ft_putchar(ptr[j++][0]);
			else if(str[i] == 'b')
				ft_putstr(ptr[j++]);
			else if(str[i] == 's')
				ft_putstr(ptr[j++]);
			else if (str[i] == '%')
				ft_putchar('%');
			else if (str[i] == 'd' || str[i] == 'i')
				ft_putstr(ptr[j++]);
			else if (str[i] == 'u')
				ft_putstr(ptr[j++]);
			else if (str[i] == 'o')
				ft_putstr(ptr[j++]);
			else if (str[i] == 'X')
				ft_putstr(ptr[j++]);
			else if (str[i] == 'x')
				ft_putstr(ptr[j++]);
			else if (str[i] == 'f')
				ft_putstr(ptr[j++]);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	return i;
}
////plus/////
char	*ft_tolow(char  *c)
{
	int i=0;
	while (c[i])
	{
		if (ft_isupper(c[i]))
			c[i] = c[i] + 32;
		i++;
	}
	return (c);
}
///////end plus////////

int flag(char *str,int i, char **ptr, int *j)
{
	char **t;
	int count=0;
	char *s;

	s = (char*)malloc(100);
	t = sort_args(str);
	if (str[i] == '+' && ft_atoi(ptr[*j]) >= 0)
	{ft_putchar('+');i++;}
	else if (str[i] == '+' && ft_atoi(ptr[*j]) < 0)
		i++;
	else if (str[i] == '*')
	{
		while((unsigned long)count < (ft_atoi(ptr[*j])-ft_strlen(ptr[*j+1])))
		{ft_putchar(' ');count++;}
		(*j)++;
		i++;
	}
	else if (str[i] == '#')
	{
		if (t[*j][0] == 'o' || t[*j][1] == 'o') 
			ft_putchar('0');
		if (t[*j][0] == 'X' || t[*j][1] == 'X') 
			ft_putstr("0X");
		if (t[*j][0] == 'x' || t[*j][1] == 'x')
			ft_putstr("0x");
		i++;
	}
	else if (str[i] == '0')
	{
		count = 0;
		while (str[i] <= '9' && str[i] >= '0')
			s[count++] = str[i++];
		count =0;
		if (ft_atoi(ptr[*j]) < 0)
		{
			ptr[*j][0] = '0';
			count = 1;
			ft_putchar('-');
		}
		if ((size_t)ft_atoi(s) > ft_strlen(ptr[*j]))
		while((unsigned long)count < (ft_atoi(s)-ft_strlen(ptr[*j])))
		{
			ft_putchar('0');
			count++;
		}
	}
	else if (str[i] == '$')
	{
		count = 0;
		i++;
		while (str[i] <= '9' && str[i] >= '0')
			s[count++] = str[i++];
		count =0;
		if (ft_atoi(ptr[*j]) < 0)
		{
			ptr[*j][0] = '$';
			count = 1;
			ft_putchar('-');
		}	
		while((unsigned long)count < (ft_atoi(s)-ft_strlen(ptr[*j])))
		{
			ft_putchar('$');
			count++;
		}
	}
	else if (str[i] == '-')
	{
		i++;
		count = 0;
		while (str[i] <= '9' && str[i] >= '0')
			s[count++] = str[i++];
		count = 0;
		ft_putstr(ptr[*j]);
		while((unsigned long)count < (ft_atoi(s)-ft_strlen(ptr[*j]) + 1))
		{
			ft_putchar(' ');
			count++;
		}
		(*j)++;
		i++;
	}
	return (i);
}

char **sort_args(char *str)
{
	int i;
	int j;
	int k;
	char **tab;

	tab = (char **)malloc(sizeof(char) * 100);

	i = 0;
	j = 0;
	k = 0;	
	while (str[i])
	{
		tab[j] = (char*)malloc(100);
		if(str[i] == '%')
		{
			i++;
			if (str[i] == '+' || str[i] == '#' || str[i] == '0' || str[i] == '$' || str[i] == '-')
				i++;
			if (str[i] == '*')
			{i++;	tab[j++][k] = '*';tab[j] = (char*)malloc(100);}

			while (str[i] <= '9' && str[i] >= '0')
				i++;

			if(str[i] == 'h')
			{
				i++;
				if(str[i] == 'h')
				{tab[j][k++] = 'z';i++;}
				else
					tab[j][k++] = 'h';
			}
			if(str[i] == 'l')	
			{
				i++;
				if(str[i] == 'l')
				{tab[j][k++] = 'q';i++;}
				else
					tab[j][k++] = 'l';
			}
			if(str[i] == 'c')
				tab[j++][k] = 'c';
			if(str[i] == 'b')
				tab[j++][k] = 'b';
			else if(str[i] == 'p')
				tab[j++][k] = 'p';
			else if(str[i] == 's')
				tab[j++][k] = 's';
			else if(str[i] == 'i' || str[i] == 'd')
				tab[j++][k] = 'd';
			else if(str[i] == 'u')
				tab[j++][k] = 'u';
			else if(str[i] == 'o')
				tab[j++][k] = 'o';
			else if(str[i] == 'X')
				tab[j++][k] = 'X';
			else if(str[i] == 'x')
				tab[j++][k] = 'x';
			else if(str[i] == 'f')
				tab[j++][k] = 'f';
		}
		k = 0;
		i++;
	}
	tab[j][++k] = '\0';
	return tab;
}

int ft_strdoub(double b)
{
	int i;

	i = 1;
	while (b > 10)
	{
		b = b/10;
		i++;
	}
	return (i);
}

char **classified(char *str, va_list args, char **ptr)
{
	int i, k, l=0, med=6;
	double fnt, fnt2;
	char **t, *v, *f, *fst;

	i = 0;	
	t = sort_args(str);
	//ft_putstr(*t);
	while (t[l])
		l++;
	ptr = (char**)malloc(sizeof(char*) * 100);
	while (i < l)
	{
		k = 0;
		if(t[i][k] == 'c')
		{ptr[i] = (char*)malloc(2);ptr[i][0] = (char)va_arg(args, int);ptr[i][1] = '\0';}
		else if(t[i][k] == 'p')
		{
			f = ft_strjoin(f, "0x");
			ptr[i] = ft_strjoin(f ,ft_itob((unsigned  long)va_arg(args, long), "0123456789abcdef"));
		}
		else if(t[i][k] == 's')
			ptr[i] = ft_strjoin(v, va_arg(args, char *));

		else if(t[i][k] == '*')
			ptr[i] = ft_strjoin(v ,ft_itoa(va_arg(args, int)));
		
		else if(t[i][k] == 'b')
			ptr[i] = ft_strjoin(v ,ft_itob((int)va_arg(args, void*), "01"));

		else if(t[i][k] == 'd')
			ptr[i] = ft_strjoin(v ,ft_itoa(va_arg(args, int)));
		else if(t[i][k] == 'l' && t[i][++k] == 'd')
			ptr[i] = ft_strjoin(v ,ft_itoa((long int)va_arg(args, int)));
		else if(t[i][k] == 'q' && t[i][++k] == 'd')
			ptr[i] = ft_strjoin(v ,ft_itoa((long long int)va_arg(args, int)));
		else if(t[i][k] == 'h' && t[i][++k] == 'd')
			ptr[i] = ft_strjoin(v ,ft_itoa((short int)va_arg(args, int)));
		else if(t[i][k] == 'z' && t[i][++k] == 'd')
			ptr[i] = ft_strjoin(v ,ft_itoa((signed char)va_arg(args, int)));

		else if(t[i][k] == 'u')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned int)va_arg(args, int), "0123456789"));
		else if(t[i][k] == 'l' && t[i][++k] == 'u')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned long int)va_arg(args, int), "0123456789"));
		else if(t[i][k] == 'q' && t[i][++k] == 'u')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned long long int)va_arg(args, int), "0123456789"));
		else if(t[i][k] == 'h' && t[i][++k] == 'u')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned short int)va_arg(args, int), "0123456789"));
		else if(t[i][k] == 'z' && t[i][++k] == 'u')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned char)va_arg(args, int), "0123456789"));

		else if(t[i][k] == 'o')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned int)va_arg(args, int), "01234567"));
		else if(t[i][k] == 'l' && t[i][++k] == 'o')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned long int)va_arg(args, int), "01234567"));
		else if(t[i][k] == 'q' && t[i][++k] == 'o')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned long long int)va_arg(args, int), "01234567"));
		else if(t[i][k] == 'h' && t[i][++k] == 'o')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned short int)va_arg(args, int), "01234567"));
		else if(t[i][k] == 'z' && t[i][++k] == 'o')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned char)va_arg(args, int), "01234567"));

		else if(t[i][k] == 'X')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned int)va_arg(args, int), "0123456789ABCDEF"));
		else if(t[i][k] == 'l' && t[i][++k] == 'X')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned long int)va_arg(args, int), "0123456789ABCDEF"));
		else if(t[i][k] == 'q' && t[i][++k] == 'X')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned long long int)va_arg(args, int), "0123456789ABCDEF"));
		else if(t[i][k] == 'h' && t[i][++k] == 'X')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned short int)va_arg(args, int), "0123456789ABCDEF"));
		else if(t[i][k] == 'z' && t[i][++k] == 'X')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned char)va_arg(args, int), "0123456789ABCDEF"));

		else if(t[i][k] == 'x')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned int)va_arg(args, int), "0123456789abcdef"));
		else if(t[i][k] == 'l' && t[i][++k] == 'x')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned long int)va_arg(args, int), "0123456789abcdef"));
		else if(t[i][k] == 'q' && t[i][++k] == 'x')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned long long int)va_arg(args, int), "0123456789abcdef"));
		else if(t[i][k] == 'h' && t[i][++k] == 'x')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned short int)va_arg(args, int), "0123456789abcdef"));
		else if(t[i][k] == 'z' && t[i][++k] == 'x')
			ptr[i] = ft_strjoin(v ,ft_itob((unsigned char)va_arg(args, int), "0123456789abcdef"));


		else if(t[i][k] == 'f' || (t[i][k] == 'l' && t[i][++k] == 'f'))
		{
			fnt = va_arg(args, double);
			fst = ft_strjoin(ft_itoa(fnt), ".");	
			fnt2 = (fnt - (int)fnt) * 1000000;
			if (fnt2 < 0)
			{fnt2 *= -1;fnt *=-1;}
			fnt2 = fnt2 + ((fnt - (int)fnt) * 1000000 - (int)fnt2);
			while (med-- - ft_strdoub(fnt2))
				fst = ft_strjoin(fst, "0");
			ptr[i] = ft_strjoin(fst, ft_itoa_base(fnt2, "0123456789"));
		}
		i++;
	}
	return ptr;
}

int ft_printf(const char *format, ...)
{
	va_list args;
	int done;
	char **ptr;

	ptr = NULL;
	va_start (args, format);
	ptr = classified((char *)format, args, ptr);
	done = catch((char *)format, ptr);
	va_end (args);
	return done;
}


