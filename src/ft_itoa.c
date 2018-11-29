/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdiab- <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 21:38:24 by zdiab-            #+#    #+#             */
/*   Updated: 2018/10/06 21:38:29 by zdiab-           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int		get_nb_size(unsigned long long int nb)
{
	unsigned long long int	size;

	size = 0;
	while (nb >= 10)
	{
		nb /= 10;
		++size;
	}
	return (size + 1);
}

char			*ft_itoa(long long int nbr)
{
	char			*str;
	unsigned long long int	nb;
	unsigned long long int	index;
	unsigned long long int	size;

	if (nbr < 0)
		nb = (unsigned long long int)(nbr * -1);
	else
		nb = (unsigned long long int)nbr;
	size = (unsigned long long int)get_nb_size(nb);
	index = 0;
	if (!(str = (char*)malloc(sizeof(char) * (size + 1 + (nbr < 0 ? 1 : 0)))))
		return (0);
	if (nbr < 0 && (str[index] = '-'))
		size++;
	index = size - 1;
	while (nb >= 10)
	{
		str[index--] = (char)(nb % 10 + 48);
		nb /= 10;
	}
	str[index] = (char)(nb % 10 + 48);
	str[size] = '\0';
	return (str);
}
