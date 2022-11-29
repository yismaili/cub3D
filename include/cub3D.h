/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:56:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/29 23:48:54 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "../libft/libft.h"
# define W_WIDTH 1020
# define W_HEIGHT 510
# define BUFF 1024

typedef struct s_floor
{
	int	r;
	int	g;
	int	b;
}	t_floor;

typedef struct s_tmp
{
	int				i;
	int				j;
	int				len;
	int				k;
	int				l;
	char			**path;
	int				check;
	int				x;
	int				y;
	int				xx;
	int				yy;
	double			y_vrtclintrsctn;
	double			x_vrticlintrsctn;
	double			x_incrmntvrtcl;
	double			y_incrmntvrtcl;
	double			x_hrzntlintrsctn;
	double			y_hrzntlintrsctn;
	double			y_incrmnt;
	double			x_incrmnt;
	int				dstnc_x;
	int				dstnc_y;
	int				steps;
	float			x_inc;
	float			y_inc;
	int				wallbottompixel;
	double			walltoppixel;
	double			textureoffsetx;
	double			textureoffsety;
	double			correctdistance;
	double			len_n;
	int				o;
	int				i_n;
	int				j_n;
	int				distancefromtop;
	unsigned int	texturecolor;
	int				n;
}	t_tmp;

typedef struct s_ceilling
{
	int	r;
	int	g;
	int	b;
}	t_ceilling;

typedef struct s_dirct
{
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
}	t_dirct;

typedef struct s_textures
{
	int		img_width;
	int		img_height;
	void	*img;
	int		*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_textures;

typedef struct s_player
{	
	double	position_x;
	double	position_y;
	double	rottangle;
	double	rottspeed;
	int		walkdrctn;
	int		walkdown;
	int		angle;
}	t_player;

typedef struct s_minimap
{
	int	mini_scaleheight;
	int	mini_scalewidth;
}	t_minimap;

typedef struct s_ray
{	
	double	rayangle;
	double	wallhit_x;
	double	wallhit_y;
	double	distance;
	double	rayfacingdown;
	double	rayfacingup;
	double	rayfacingright;
	double	rayfacingleft;
	double	horzwallhitx;
	double	horzwallhity;
	double	vrticlwallhitx;
	double	vrtclwallhity;
	int		check;
}	t_ray;

typedef struct s_struct
{
	char			**map;
	t_ceilling		clg;
	t_floor			flr;
	t_dirct			drct;
	int				height;
	int				width;
	t_textures		*texture;
	int				len_ofmap;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				bits_per_pixel2;
	int				line_length;
	int				size_line;
	int				endian;
	int				endian2;
	int				scaleheight;
	int				scalewidth;
	t_player		player;
	double			numofrays;
	t_ray			ray;
	t_minimap		mini_map;
	int				heightof_minimap;
	int				widthof_minimap;
	char			**my_map;
	double			wallstripheight;
	int				check_test;
	unsigned int	**color_buffer;
	int				widthofmap;
	int				heightofmap;
	unsigned int	*walltexture;
	int				texture_width;
	int				texture_height ;
	void			*img2;
	int				*data;
	int				med_x;
	t_tmp			tmp;
	double			angleincrem;
}	t_struct;
int		get_height(char *map_file);
int		get_width(char *map_file, int height);
int		ft_check_map(t_struct *cub);
char	*get_next_line(int fd);
int		ft_read_maps(char *map_file, t_struct *ptr);
char	*ft_check_texture(t_struct *cub, char *dirct, int len);
char	*ft_search_innewmap(char **new_map, char *search, int len_ofsrch);
int		ft_check_alltextures(t_struct *cub);
char	**ft_check_florclg(t_struct *cub, char *flor_clg, int len);
int		ft_check_rgb(t_struct *cub);
int		ft_check_double(t_struct *cub, char *dirct, int len);
int		ft_check_alldouble(t_struct *cub);
int		ft_check_bgnend(char *data);
char	*ft_strdup_map(const char *s1, int len);
int		ft_check_openmap(char **data);
char	**ft_split_map(t_struct *cub);
char	*ft_search_inmap(t_struct *cub, char *search, int len_ofsrch);
void	ft_draw_map(t_struct *cub);
void	player_position(t_struct *cub);
int		player_move(t_struct *cub);
void	direction_of_player(t_struct *cub);
void	dda(t_struct *cub, int x_0, int y_0);
int		check_wall(t_struct *cub, double x, double y);
void	randering_wall(t_struct *cub);
int		castRays(t_struct *cub);
void	check_nextsteep(t_struct *cub);
void	check_downsteep(t_struct *cub);
double	normalize_angle(double angle);
double	calcul_distance(double wallHit_X, double wallHit_y, double x, double y);
void	cast_hrzntal_rays(t_struct *cub);
void	cast_vrtcal_rays(t_struct *cub);
void	cast_all_rays(t_struct *cub);
void	drawrays_of_plyer_mini(t_struct *cub, int x, int y);
int		ft_count_height(t_struct *cub);
void	my_mlx_pixel_put(t_struct *ptr, int x, int y, unsigned int color);
void	ft_jump_lines(t_struct *cub);
void	ft_color_buffer(t_struct *cub);
double	degrees_to_radians(double a);
int		key_release(int key, t_struct *cub);
int		key_press(int key, t_struct *cub);
int		handling_rgb(char *data);
int		ft_check_isnum(char *num);
int		typeof_file(char *path, char *type, int len);
void	loading_map(t_struct *cub);
int		motion_notify(int x, int y, t_struct *cub);
int		ft_close(int keycode);
void	set_map(t_struct *cub, int len);
void	free_map(char **ptr);
int		check_elmntof_map(t_struct *cub);
char	**convert_tonum(char **splt_data);
void	remplir_rgb_flor(t_struct *cub, char **splt_dataflr);
int		len_ofpath(char *path);
void	init_textures(t_struct *cub);
int		motion_notify(int x, int y, t_struct *cub);
int		typeofmap(char *path, char *type, int len);
void	load_texture(t_struct *c, t_textures *t);
void	color_oftexture(t_struct *cub);
void	init_dataray(t_struct *cub);
void	searchto_wall_vrtcl(t_struct *cub);
void	searchto_wall_hrzntl(t_struct *cub);
void	set_texturecolor(t_struct *cub);
void	calcul_heigtof_wall(t_struct *cub);
void	calcul_texture_pixls(t_struct *cub);

#endif
