/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 21:31:33 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/04 23:23:08 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	sl_updatetexture_ids(t_game *game)
{
	static struct timespec	prev_time = (struct timespec){0};
	struct timespec			curr_time;
	size_t					seconds_diff;
	size_t					nano_diff;
	double					diff;

	clock_gettime(CLOCK_REALTIME, &curr_time);
	seconds_diff = curr_time.tv_sec - prev_time.tv_sec;
	nano_diff = curr_time.tv_nsec - prev_time.tv_nsec;
	if (curr_time.tv_nsec < prev_time.tv_nsec)
	{
		seconds_diff--;
		nano_diff = 1000000000L + curr_time.tv_nsec - prev_time.tv_nsec;
	}
	else
		nano_diff = curr_time.tv_nsec - prev_time.tv_nsec;
	diff = seconds_diff + nano_diff / 1.0e9;
	if (diff < 1.0 / FPS)
		return ;
	prev_time = curr_time;
	game->imgs.pll_idx++;
	game->imgs.plr_idx++;
	game->imgs.pll_idx = game->imgs.pll_idx % SLA_PLAYER_COUNT;
	game->imgs.plr_idx = game->imgs.plr_idx % SLA_PLAYER_COUNT;
}

bool	sl_show_texts(t_game *game)
{
	const int		size = SL_TILESIZE;
	char			*moves;
	const t_point	pos = game->meta.position;
	const t_point	cntr = {game->meta.map.size.x / 2 * size - 15,
		game->meta.map.size.y / 2 * size};
	char			*msg;

	moves = ft_itoa(game->meta.moves);
	if (game->meta.dead)
		mlx_string_put(game->mlx, game->window, cntr.x, cntr.y, 0xffc800,
			"You've been overflowed by bugs.");
	if (!game->meta.game_finished && !game->meta.dead)
		mlx_string_put(game->mlx, game->window, pos.x * size + (size * .5)
			- ft_nbr_len(game->meta.moves, 10) * size * .05,
			pos.y * size - 5, 0xffc800, (char *)moves);
	msg = ft_strjoin("Total moves: ", (char *)moves);
	if (game->meta.game_finished)
	{
		mlx_string_put(game->mlx, game->window, cntr.x, cntr.y - 15, 0xffc800,
			"You won! GG");
		mlx_string_put(game->mlx, game->window, cntr.x, cntr.y, 0xffc800, msg);
	}
	return (free(msg), free(moves), true);
}

void	draw_texture(t_game *game, char id, int x, int y)
{
	t_img				*img;

	if (id == PLAYER && game->meta.facing == FACE_RIGHT)
		img = game->imgs.player_r[game->imgs.plr_idx];
	else if (id == PLAYER && game->meta.facing == FACE_LEFT)
		img = game->imgs.player_l[game->imgs.pll_idx];
	else if (id == EXIT && !game->meta.collect_cty)
		img = game->imgs.exit_ok;
	else if (id == EXIT)
		img = game->imgs.exit_ko;
	else if (id == WALL)
		img = game->imgs.wall;
	else if (id == FLOOR)
		img = game->imgs.floor;
	else if (id == COLLECTIBLE)
		img = game->imgs.collectible;
	else if (id == ENEMY)
		img = game->imgs.enemy;
	else
		return ;
	sl_draw_img(game, img, x, y);
}

int	sl_render(t_game *game)
{
	int		i;
	int		j;

	i = -1;
	while (++i < game->meta.map.size.y)
	{
		j = -1;
		while (++j < game->meta.map.size.x)
			draw_texture(game, game->map[i][j], j, i);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->atlas, 0, 0);
	mlx_string_put(game->mlx, game->window, 5, 15, 0xf08155, "ESC: exit");
	if (!game->meta.dead && !game->meta.game_finished)
		mlx_string_put(game->mlx, game->window, 5, 30, 0xf08155,
			"WASD: Movement");
	sl_show_texts(game);
	sl_updatetexture_ids(game);
	return (0);
}
