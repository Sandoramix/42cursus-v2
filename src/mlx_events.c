/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 19:26:27 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/05 01:14:41 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	sl_cleanup(t_game *game, bool should_exit, int status)
{
	ft_freemtx(game->map, game->meta.map.size.y);
	ft_lstclear(&game->meta.enemies_pos, &free);
	if (game->mlx != NULL)
	{
		destroy_textures(game);
		mlx_clear_window(game->mlx, game->window);
		mlx_destroy_window(game->mlx, game->window);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (should_exit)
		exit(status);
	return (status);
}

int	sl_ondestroy(t_game *game)
{
	sl_cleanup(game, true, 0);
	return (0);
}

static t_point	get_nextmove(t_game *game, int key)
{
	t_point				nextmove;

	nextmove = game->meta.position;
	if (!is_known_key(key))
		return (nextmove);
	if (key == SL_UP)
		nextmove.y--;
	else if (key == SL_DOWN)
		nextmove.y++;
	if (key == SL_LEFT)
	{
		game->meta.facing = FACE_LEFT;
		nextmove.x--;
	}
	else if (key == SL_RIGHT)
	{
		game->meta.facing = FACE_RIGHT;
		nextmove.x++;
	}
	return (nextmove);
}

int	sl_onkeypressed(int key, t_game *game)
{
	t_point		*currpos;
	t_point		nextmove;

	if (key == SL_QUIT)
		return (sl_cleanup(game, true, 0));
	nextmove = get_nextmove(game, key);
	currpos = &game->meta.position;
	if (!is_known_key(key) || game->meta.dead
		|| !can_player_movehere(game->map, game->meta, nextmove))
		return (0);
	game->meta.moves++;
	game->map[currpos->y][currpos->x] = FLOOR;
	if (game->map[nextmove.y][nextmove.x] == COLLECTIBLE)
		game->meta.collect_cty--;
	if (game->map[nextmove.y][nextmove.x] == EXIT && !game->meta.collect_cty)
		game->meta.game_finished = true;
	if (game->map[nextmove.y][nextmove.x] == ENEMY)
		game->meta.dead = true;
	else
		game->map[nextmove.y][nextmove.x] = PLAYER;
	*(currpos) = (t_point){nextmove.x, nextmove.y};
	sl_move_enemies(game);
	return (0);
}
