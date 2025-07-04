/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:09:42 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/05 00:57:19 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	chk_badborders(char **map, t_meta *meta)
{
	int	i;
	int	j;

	if (meta->map.size.y > 0)
		meta->map.badborders += ft_strlen(map[0]) - ft_strcount_c(map[0], WALL);
	if (meta->map.size.y > 1)
		meta->map.badborders += ft_strlen(map[meta->map.size.y - 1])
			- ft_strcount_c(map[meta->map.size.y - 1], WALL);
	i = 0;
	while (++i < meta->map.size.y - 1)
	{
		j = ft_istrlen(map[i]);
		if (j > 0 && !sl_iswall(map[i][j - 1]))
			meta->map.badborders++;
		if (!sl_iswall(map[i][0]))
			meta->map.badborders++;
	}
	return (meta->map.badborders > 0);
}

static void	count_chars(char **map, t_meta *meta)
{
	int	i;
	int	j;

	i = -1;
	while (++i < meta->map.size.y)
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr(SL_ALLOWEDCHARS, map[i][j]))
				meta->map.badchars++;
			else if (map[i][j] == PLAYER)
				meta->position = (t_point){j, i};
			else if (map[i][j] == EXIT)
				meta->exitpoint = (t_point){j, i};
			else if (map[i][j] == ENEMY)
				sl_add_enemy(meta, j, i);
		}
		meta->map.players_cty += ft_strcount_c(map[i], PLAYER);
		meta->collect_cty += ft_strcount_c(map[i], COLLECTIBLE);
		meta->map.exits_cty += ft_strcount_c(map[i], EXIT);
		meta->map.badsize |= meta->map.size.x != ft_istrlen(map[i]);
	}
}

t_meta	*sl_parsemap(t_game *game, char **map)
{
	t_meta	*m;

	m = &game->meta;
	ft_bzero(m, sizeof(t_meta));
	m->map.size.y = ft_memmtxlen(map);
	m->facing = FACE_RIGHT;
	if (m->map.size.y > 0)
		m->map.size.x = ft_strlen(map[0]);
	count_chars(map, m);
	if (m->map.players_cty != 1 || m->collect_cty < 1
		|| m->map.exits_cty != 1 || m->map.size.y == m->map.size.x)
		m->map.badsize = true;
	chk_badborders(map, m);
	parse_ispathvalid(game, m);
	m->map.valid = !m->map.badborders && !m->map.badchars
		&& m->collect_cty > 0 && m->map.exits_cty == 1
		&& m->map.players_cty == 1 && !m->map.badsize && !m->map.badpath;
	return (m);
}

int	sl_parse(int ac, char **av, t_game *game)
{
	int	fd;

	if (ac != 2)
		return (sl_helpmsg(game, av[0]));
	if (!ft_strendswith(av[1], ".ber"))
	{
		ft_printf(COLOR_RED"Error\nMap extension must be \".ber\"\n");
		return (sl_helpmsg(game, av[0]));
	}
	fd = open(av[1], O_RDONLY);
	if (fd <= 0)
		return (ft_perror("Error\nCannot open %s file\n", av[1]));
	game->map = ft_readfile(fd, false);
	close(fd);
	sl_parsemap(game, game->map);
	if (!game->meta.map.valid)
		return (sl_errmsg(game->meta));
	return (0);
}
