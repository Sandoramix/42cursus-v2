/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 19:15:17 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/05 00:59:00 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

/**
 * `true` = can move, `false` = cannot
 */
static bool	move_enemy(char **map, t_meta *meta, t_point *curr)
{
	const int	all[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	int			choice;
	t_point		newpos;

	choice = rand() % 4;
	newpos = (t_point){curr->x + all[choice][0], curr->y + all[choice][1]};
	if (!can_enemy_movehere(map, *meta, newpos))
		return (false);
	map[curr->y][curr->x] = FLOOR;
	*(curr) = newpos;
	map[newpos.y][newpos.x] = ENEMY;
	return (true);
}

void	sl_move_enemies(t_game *game)
{
	t_list		*enemy;
	int			tries;

	enemy = game->meta.enemies_pos;
	tries = 0;
	srand(time(NULL));
	while (enemy)
	{
		if (!move_enemy(game->map, &game->meta, (t_point *)enemy->content)
			&& tries++ < 3)
			continue ;
		if (((t_point *)enemy->content)->y == game->meta.position.y
			&& ((t_point *)enemy->content)->x == game->meta.position.x)
			game->meta.dead = true;
		tries = 0;
		enemy = enemy->next;
	}
}

void	sl_add_enemy(t_meta *meta, int x, int y)
{
	t_point	*point;

	point = ft_calloc(1, sizeof(t_point));
	if (!point)
	{
		ft_printf("FAILED TO ADD ENEMY MOVEMENT HANDLING at x[%d] y[%d]", x, y);
		ft_printf(COLOR_YELLOW"\nIt wont be able to move :)\n"CR);
		return ;
	}
	point->x = x;
	point->y = y;
	ft_lstadd_back(&meta->enemies_pos, ft_lstnew(point));
}
