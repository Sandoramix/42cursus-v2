/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:42:44 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/05 01:00:18 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	sl_game_init(t_game *game)
{
	game->meta.dead = false;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (ft_perror("There was an error with connection to X server\n"));
	load_all_textures(game);
	game->window = mlx_new_window(game->mlx,
			game->meta.map.size.x * SL_TILESIZE,
			game->meta.map.size.y * SL_TILESIZE,
			"SO LONG");
	game->atlas = mlx_new_image(game->mlx, game->meta.map.size.x * SL_TILESIZE,
			game->meta.map.size.y * SL_TILESIZE);
	if (!game->atlas)
	{
		ft_perror("Could not create atlas image\n");
		sl_cleanup(game, true, 1);
	}
	mlx_hook(game->window, DestroyNotify, StructureNotifyMask, &sl_ondestroy,
		game);
	mlx_hook(game->window, KeyPress, KeyPressMask, &sl_onkeypressed, game);
	mlx_loop_hook(game->mlx, &sl_render, game);
	mlx_loop(game->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	game.meta = (t_meta){0};
	game.meta.map = (t_mapmeta){0};
	game.imgs = (t_textures){0};
	game.mlx = NULL;
	if (sl_parse(ac, av, &game))
		return (sl_cleanup(&game, true, 1));
	return (sl_game_init(&game));
}
