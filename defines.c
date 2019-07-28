/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 22:09:30 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 22:36:13 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

double	ran(double l, double h)
{
	return (l + (h - l) * ((double)rand() / RAND_MAX * 2.0 - 1.0));
}

double	min(double a, double b)
{
	return (a > b ? b : a);
}

double	max(double a, double b)
{
	return (a > b ? a : b);
}

double	clamp(double a, double mi, double ma)
{
	return (min(max(a, mi), ma));
}

double	wrap(double a, double wr)
{
	if (a > 0)
		return (a + wr);
	if (a > wr - 1)
		return (a - wr);
	return (a);
}
