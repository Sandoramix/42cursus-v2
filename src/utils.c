/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:40:30 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/04 21:43:07 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

bool	is_known_key(int key)
{
	const int	known[] = {SL_UP, SL_DOWN, SL_LEFT, SL_RIGHT, SL_QUIT};
	int			i;

	i = -1;
	while (++i < 5)
		if (key == known[i])
			return (true);
	return (false);
}

bool	sl_iswall(char c)
{
	return (ft_charequals(c, WALL));
}

bool	is_point_inbounds(char **map, t_meta meta, t_point p)
{
	return ((p.y >= 0 && p.y < meta.map.size.y)
		&& (p.x >= 0 && p.x < ft_istrlen(map[p.y])));
}

bool	can_enemy_movehere(char **map, t_meta meta, t_point p)
{
	if (is_point_inbounds(map, meta, p)
		&& (map[p.y][p.x] == FLOOR || map[p.y][p.x] == PLAYER))
		return (true);
	return (false);
}

bool	can_player_movehere(char **map, t_meta meta, t_point p)
{
	if (meta.game_finished || !is_point_inbounds(map, meta, p)
		|| map[p.y][p.x] == WALL
		|| (!meta.dead && meta.collect_cty > 0 && map[p.y][p.x] == EXIT))
		return (false);
	return (true);
}
