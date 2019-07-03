/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:39:25 by njacobso          #+#    #+#             */
/*   Updated: 2019/04/14 17:48:50 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_abs(int num)
{
	unsigned int number;

	if (num == -2147483648)
		return (-1);
	if (num < 0)
		number = -num;
	else
		number = num;
	return (number);
}
