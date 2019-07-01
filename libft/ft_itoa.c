/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 20:27:39 by njacobso          #+#    #+#             */
/*   Updated: 2018/12/15 16:58:39 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	str_len(int n)
{
	size_t i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char		*ft_itoa(int n)
{
	char			*str;
	size_t			size;
	unsigned int	num;

	size = str_len(n);
	if (n < 0)
	{
		num = -n;
		size++;
	}
	else
		num = n;
	str = ft_strnew(size);
	if (!str)
		return (NULL);
	str[--size] = num % 10 + '0';
	while (num /= 10)
		str[--size] = num % 10 + '0';
	if (n < 0)
		str[0] = '-';
	return (str);
}
