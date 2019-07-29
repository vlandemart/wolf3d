/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:41:42 by njacobso          #+#    #+#             */
/*   Updated: 2019/04/14 17:48:58 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_pow(int num, int pow)
{
	int current_pow;
	int nbr;

	if (pow == 0)
		return (1);
	current_pow = pow;
	nbr = num;
	while (current_pow > 1)
	{
		nbr *= num;
		current_pow--;
	}
	return (nbr);
}
