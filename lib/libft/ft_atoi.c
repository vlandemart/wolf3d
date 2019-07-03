/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 12:02:05 by njacobso          #+#    #+#             */
/*   Updated: 2019/02/16 12:53:05 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static int	is_separator(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n' ||
		ch == '\r' || ch == '\v' || ch == '\f')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	int				i;
	unsigned long	num;
	int				sign;

	i = 0;
	num = 0;
	sign = 1;
	while (is_separator(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i++] - '0');
		if (num > 9223372036854775807U && sign == 1)
			return (-1);
		if (num > 9223372036854775808U && sign == -1)
			return (0);
	}
	num = num * sign;
	return ((int)num);
}
