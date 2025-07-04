/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:04:03 by odudniak          #+#    #+#             */
/*   Updated: 2025/07/05 00:57:08 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <time.h>
# include <X.h>
# include <keysym.h>
# include <keysymdef.h>

# include <mlx.h>
# include <mlx_int.h>

# include <libft.h>
# include <sl_settings.h>
# include <sl_assets.h>
# include <sl_structs.h>

// ! EXTRA (NEEDED FOR SPRITES RENDER LIMITING)
bool	sl_show_texts(t_game *game);
void	sl_updatetexture_ids(t_game *game);

bool	can_enemy_movehere(char **map, t_meta meta, t_point p);
bool	can_player_movehere(char **map, t_meta meta, t_point p);
void	destroy_textures(t_game *game);
void	draw_on_atlas(t_game *game, t_img *img, t_point a_pos, t_point tex_pos);
void	draw_texture(t_game *game, char id, int x, int y);
bool	is_known_key(int key);
bool	is_point_inbounds(char **map, t_meta meta, t_point p);
void	load_all_textures(t_game *game);
t_img	*load_texture(t_game *game, char *xpm_path);
int		main(int ac, char **av);
bool	parse_ispathvalid(t_game *game, t_meta *meta);
void	sl_add_enemy(t_meta *meta, int x, int y);
int		sl_cleanup(t_game *game, bool should_exit, int status);
void	sl_draw_img(t_game *game, t_img *img, int x, int y);
int		sl_errmsg(t_meta m);
int		sl_game_init(t_game *game);
int		sl_helpmsg(t_game *game, char *progname);
bool	sl_iswall(char c);
void	sl_move_enemies(t_game *game);
int		sl_ondestroy(t_game *game);
int		sl_onkeypressed(int key, t_game *game);
int		sl_parse(int ac, char **av, t_game *game);
t_meta	*sl_parsemap(t_game *game, char **map);
int		sl_render(t_game *game);

#endif