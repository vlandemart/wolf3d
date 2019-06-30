/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 22:52:21 by ydavis            #+#    #+#             */
/*   Updated: 2018/11/29 17:52:36 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_digit(int n)
{
	size_t ret;

	ret = 1;
	while (n >= 10)
	{
		n /= 10;
		ret++;
	}
	return (ret);
}

static char		ft_append_c(int n, size_t i)
{
	size_t	count;

	count = 0;
	while (count < i)
	{
		count++;
		n /= 10;
	}
	return ((n % 10) + '0');
}

char			*ft_itoa(int n)
{
	char	*ret;
	size_t	count;
	size_t	i;
	size_t	flag;

	if (n == 2147483647)
		return (ft_strdup("2147483647"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	flag = 0;
	if (n < 0 && (flag = 1))
		n *= -1;
	if (!(count = ft_count_digit(n) + flag)
			|| !(ret = (char*)malloc(sizeof(char) * (count + 1))))
		return (NULL);
	if (flag)
		ret[0] = '-';
	i = flag;
	while (i < count)
	{
		ret[count - i - 1 + flag] = ft_append_c(n, i - flag);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
