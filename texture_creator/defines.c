/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 20:54:22 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/29 20:55:26 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_creator.h"

double	max(double a, double b)
{
	return (a > b ? a : b);
}

double	min(double a, double b)
{
	return (a > b ? b : a);
}

double	clamp(double a, double mi, double ma)
{
	return (min(max(a, mi), ma));
}
