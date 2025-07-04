/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:04:39 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/04 23:22:49 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	sl_errmsg(t_meta m)
{
	ft_perror("[MAP ERROR]\t");
	if (m.map.badchars > 0)
		ft_perror("Map contains %d invalid characters.", m.map.badchars);
	else if (m.map.badborders)
		ft_perror("The map has to be surrounded by walls.");
	else if (m.map.players_cty > 1)
		ft_perror("There can be only one spawnpoint.");
	else if (m.map.exits_cty > 1)
		ft_perror("There can be only one exit.");
	else if (m.collect_cty < 1)
		ft_perror("There are not enough collectibles.");
	else if (m.map.badpath)
		ft_perror("The game cannot be finished because of a bad path.");
	else if (m.map.badsize && m.map.size.x == m.map.size.y)
		ft_perror("Map must be rectangular.");
	else if (m.map.badsize)
		ft_perror("Map size is invalid.");
	if (m.map.badpath && m.collect_cty != m.map.coll_cty)
		ft_perror("\n\t\tReachable collectibles: %d / %d", m.map.coll_cty,
			m.collect_cty);
	ft_perror("\n");
	return (1);
}

int	sl_helpmsg(t_game *game, char *progname)
{
	ft_printf(COLOR_YELLOW"Usage: "COLOR_CYAN"%s <path_to_map>\n"CR, progname);
	return (sl_cleanup(game, true, 1));
}
