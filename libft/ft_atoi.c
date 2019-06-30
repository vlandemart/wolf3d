/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 23:03:20 by ydavis            #+#    #+#             */
/*   Updated: 2018/11/30 23:16:34 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int	ft_check_func(long ret, int count, int flag)
{
	int i;
	int flagtmp;

	i = 0;
	flagtmp = 0;
	if (ret < 0)
	{
		ret *= -1;
		flagtmp = 1;
	}
	while (ret)
	{
		ret /= 10;
		i++;
	}
	if (flag < 0)
		count--;
	if (i < count)
	{
		if (flag == -1)
			return (0);
		else
			return (-1);
	}
	return (1);
}

int			ft_atoi(const char *str)
{
	int		i;
	long	ret;
	int		flag;

	flag = 1;
	i = 0;
	ret = 0;
	while (((*str <= 13 && *str >= 9) || *str == ' ') && *str)
		str++;
	if (str[i] == '-')
	{
		flag = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] == '0')
		str++;
	while (str[i] <= '9' && str[i] >= '0' && str[i])
		ret = ret * 10 + str[i++] - '0';
	if (ft_check_func(ret, i - 1, flag) != 1)
		return (ft_check_func(ret, i, flag));
	return (ret * flag);
}
