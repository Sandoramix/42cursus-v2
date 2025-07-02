/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 08:58:43 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/02 10:19:08 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	draw_on_atlas(t_game *game, t_img *img, t_point a_pos, t_point tex_pos)
{
	char		*dest;
	char		*src;

	dest = game->atlas->data
		+ game->atlas->size_line * a_pos.y + a_pos.x * (game->atlas->bpp / 8);
	src = img->data
		+ img->size_line * tex_pos.y + tex_pos.x * (img->bpp / 8);
	ft_memcpy(dest, src, sizeof(char) * 4);
}

void	sl_draw_img(t_game *game, t_img *img, int x, int y)
{
	const int			x_px = x * SL_TILESIZE;
	const int			y_px = y * SL_TILESIZE;
	int					i;
	int					j;

	i = -1;
	while (++i < SL_TILESIZE)
	{
		j = -1;
		while (++j < SL_TILESIZE)
		{
			draw_on_atlas(game, img,
				(t_point){.x = x_px + j, .y = y_px + i},
				(t_point){.x = (float)j / (float)SL_TILESIZE * img->width,
				.y = (float)i / (float)SL_TILESIZE * img->height});
		}
	}
}
