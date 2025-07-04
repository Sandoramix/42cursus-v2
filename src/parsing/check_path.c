/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 22:04:19 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/04 23:23:43 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

/**
 * DFS path validation
 * 
 * @return `true` if path is valid (can reach collectibles and the exit)
 * @return `false` if path is invalid (can't reach collectibles or the exit)
 */
static bool	is_path_reachable(char **map, t_meta *meta, t_point p)
{
	const int	moves[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	bool		valid;
	int			i;
	t_point		next;

	if (!is_point_inbounds(map, *meta, p))
		return (false);
	if (map[p.y][p.x] == WALL || map[p.y][p.x] == 42)
		return (false);
	if (map[p.y][p.x] == EXIT)
		return (true);
	if (map[p.y][p.x] == COLLECTIBLE)
		meta->map.coll_cty += 1;
	map[p.y][p.x] = 42;
	i = -1;
	valid = false;
	while (++i < 4)
	{
		next = (t_point){p.x + moves[i][0], p.y + moves[i][1]};
		valid = is_path_reachable(map, meta, next) || valid;
	}
	return (valid);
}

bool	parse_ispathvalid(t_game *game, t_meta *meta)
{
	char	**mcopy;
	bool	valid;

	mcopy = ft_strmtxdup(game->map);
	if (!mcopy)
		return (ft_perror("Failed to duplicate map\n"),
			sl_cleanup(game, true, 1), false);
	valid = is_path_reachable(mcopy, meta, meta->position);
	meta->map.badpath |= !valid || meta->map.coll_cty != meta->collect_cty;
	if (SL_DEBUG)
	{
		ft_printf(COLOR_CYAN"\nDFS PATH VALIDATION:\n");
		ft_putstrmtx(mcopy);
		ft_printf(CR);
	}
	ft_freemtx(mcopy, ft_memmtxlen(mcopy));
	return (valid);
}
