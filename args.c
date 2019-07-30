/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 21:59:00 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 22:01:50 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_args(t_wf *wf, int ac, char **av)
{
	if (ac == 2)
	{
		if (read_map(wf, av[1]) != 1)
		{
			ft_putendl("Error reading map!");
			exit(0);
		}
	}
	else
	{
		ft_putendl("No map passed, initing empty room.");
		wf->map_size = 10;
		init_map(wf);
	}
}
