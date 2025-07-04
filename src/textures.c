/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:22:33 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/05 00:59:51 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

t_img	*load_texture(t_game *game, char *xpm_path)
{
	int		width;
	int		height;
	t_img	*res;

	res = mlx_xpm_file_to_image(game->mlx, xpm_path, &width,
			&height);
	if (!res)
	{
		ft_printf(COLOR_RED
			"ERROR WHILE GENERATING TEXTURE located at [%s].\nAborting...\n"CR,
			xpm_path);
		sl_cleanup(game, true, 1);
	}
	return (res);
}

static t_img	**load_player_textures(t_game *game, char *filenames[])
{
	const int	len = SLA_PLAYER_COUNT;
	int			i;
	t_img		**res;

	res = ft_calloc(len + 1, sizeof(t_img *));
	if (!res)
	{
		ft_printf(COLOR_RED"MALLOC ERROR ON PLAYER TEXTURES.\nAborting...\n"CR);
		sl_cleanup(game, true, 1);
	}
	i = -1;
	while (++i < len)
		res[i] = load_texture(game, filenames[i]);
	return (res);
}

void	load_all_textures(t_game *game)
{
	char	**pl;
	char	**pr;
	char	*tmp;
	int		i;

	i = -1;
	pl = ft_calloc(SLA_PLAYER_COUNT + 1, sizeof(char *));
	pr = ft_calloc(SLA_PLAYER_COUNT + 1, sizeof(char *));
	while (++i < SLA_PLAYER_COUNT)
	{
		tmp = ft_str_freejoin(ft_itoa(i + 1), ".xpm");
		pl[i] = ft_strjoin(SLA_PLAYER_L_PREFIX, tmp);
		pr[i] = ft_strjoin(SLA_PLAYER_R_PREFIX, tmp);
		free(tmp);
	}
	game->imgs.floor = load_texture(game, SLA_FLOOR);
	game->imgs.exit_ko = load_texture(game, SLA_EXIT_KO);
	game->imgs.exit_ok = load_texture(game, SLA_EXIT_OK);
	game->imgs.wall = load_texture(game, SLA_WALL);
	game->imgs.collectible = load_texture(game, SLA_COLLECTIBLE);
	game->imgs.enemy = load_texture(game, SLA_ENEMY);
	game->imgs.player_l = load_player_textures(game, pl);
	game->imgs.player_r = load_player_textures(game, pr);
	ft_freemtx(pl, SLA_PLAYER_COUNT);
	ft_freemtx(pr, SLA_PLAYER_COUNT);
}

void	destroy_textures(t_game *game)
{
	int	i;

	mlx_destroy_image(game->mlx, game->imgs.floor);
	mlx_destroy_image(game->mlx, game->imgs.exit_ko);
	mlx_destroy_image(game->mlx, game->imgs.exit_ok);
	mlx_destroy_image(game->mlx, game->imgs.wall);
	mlx_destroy_image(game->mlx, game->imgs.collectible);
	mlx_destroy_image(game->mlx, game->imgs.enemy);
	i = -1;
	while (game->imgs.player_l[++i])
		mlx_destroy_image(game->mlx, game->imgs.player_l[i]);
	free(game->imgs.player_l);
	i = -1;
	while (game->imgs.player_r[++i])
		mlx_destroy_image(game->mlx, game->imgs.player_r[i]);
	free(game->imgs.player_r);
	mlx_destroy_image(game->mlx, game->atlas);
}
