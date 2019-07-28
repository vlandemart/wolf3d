/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 20:21:20 by ydavis            #+#    #+#             */
/*   Updated: 2019/07/28 20:29:48 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	update(t_wf *wf, int flag)
{
	if (flag)
		ft_memset(wf->sdl->pix, 0, wf->width * wf->height * sizeof(Uint32));
	SDL_UpdateTexture(wf->sdl->txt, NULL, wf->sdl->pix,
			wf->width * sizeof(Uint32));
	SDL_RenderClear(wf->sdl->ren);
	SDL_RenderCopy(wf->sdl->ren, wf->sdl->txt, NULL, NULL);
	SDL_RenderPresent(wf->sdl->ren);
}
