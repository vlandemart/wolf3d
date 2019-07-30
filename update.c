/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:21:20 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/30 07:43:10 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	update(t_wf *wf, int flag)
{
	if (flag)
		ft_memset(wf->sdl->pix, 0, wf->width * wf->height * sizeof(Uint32));
	if (SDL_UpdateTexture(wf->sdl->txt, NULL, wf->sdl->pix,
			wf->width * sizeof(Uint32)))
		simclose("Unexpected error with SDL.");
	if (SDL_RenderClear(wf->sdl->ren))
		simclose("Unexpected error with SDL.");
	if (SDL_RenderCopy(wf->sdl->ren, wf->sdl->txt, NULL, NULL))
		simclose("Unexpected error with SDL.");
	SDL_RenderPresent(wf->sdl->ren);
}
