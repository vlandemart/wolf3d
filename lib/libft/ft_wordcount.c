/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:58:08 by njacobso          #+#    #+#             */
/*   Updated: 2018/12/15 17:58:21 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_wordcount(char const *str, char splitter)
{
	int i;
	int sum;

	i = 0;
	sum = 0;
	while (str[i])
	{
		while (str[i] && str[i] == splitter)
			i++;
		if (str[i] && str[i] != splitter)
			sum++;
		while (str[i] && str[i] != splitter)
			i++;
	}
	return (sum);
}
