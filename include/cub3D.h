/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:56:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/27 17:56:47 by yismaili         ###   ########.fr       */
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
//# include "../minilibx_opengl_20191021/mlx.h"
# define W_WIDTH 1020
# define W_HEIGHT 510
# define BUFF 1024

typedef struct s_floor
{
	int r;
	int g;
	int b;
}	t_floor;

typedef struct s_ceilling
{
	int r;
	int g;
	int b;
}	t_ceilling;

typedef struct s_dirct
{
	char 	*north_path;
	char 	*south_path;
	char 	*west_path;
	char 	*east_path;
	
}	t_dirct;
typedef struct  s_player{
	
	double	position_x;
	double 	position_y;
	double 	rottAngle;
	double  rottSpeed;
	int 	walkDrctn;
	int		walkDown;
	int		angle;
	
}  t_player;
typedef struct  s_minimap{
	int 	mini_scaleHeight;
	int 	mini_scaleWidth;
}  t_minimap;

typedef struct  s_ray{
	
	double 	rayAngle;
	double 	wallHit_x;
	double	wallHit_y;
	double 	Distance;
	double  rayFacingDown;
	double	rayFacingUp;
	double  rayFacingRight;
	double	rayFacingLeft;
	double  horzWallHitX;
    double  horzWallHitY;
	double  vrticlWallHitX;
    double  vrtclWallHitY;
	int check;
	
}  t_ray;

typedef struct s_struct
{
	char			**map;
	t_ceilling 		clg;
	t_floor			flr;
	t_dirct			drct;
	int				height;
	int				width;
	int				len_ofmap;
	void			*mlx_ptr;
    void			*win_ptr;
	void			*img;
	int 			*addr;
	int				bits_per_pixel;
	int				bits_per_pixel2;
	int				line_length;
	int				size_line;
	int				endian;
	int				endian2;
	int 			scaleHeight;
	int 			scaleWidth;
	t_player 		player;
	double			numOfRays;
	t_ray       	ray;
	t_minimap		mini_map;
	int				heightof_minimap;
	int				widthof_minimap;
	char			**my_map;
	double			wallStripHeight;
	int				check_test;
	unsigned int 	**color_buffer;
	int				widthofmap;
	int				heightofmap;
	unsigned int 	*wallTexture;
	int				texture_width;
	int 			texture_height ;
	void			*img2;
	int 			*data;
	int				med_x;
	
}	t_struct;


int     get_height(char *map_file);
int		get_width(char *map_file, int height);
int	    ft_check_map(t_struct *cub);
char	*get_next_line(int fd);
int		ft_read_maps(char *map_file, t_struct *ptr);
char    *ft_check_texture(t_struct *cub, char *dirct, int len);
char    *ft_search_innewmap(char **new_map, char *search, int len_ofsrch);
int		ft_check_alltextures(t_struct *cub);
char    **ft_check_florclg(t_struct *cub, char *flor_clg, int len);
int		ft_check_rgb(t_struct *cub);
int		ft_check_double(t_struct *cub, char *dirct, int len);
int		ft_check_alldouble(t_struct *cub);
int 	ft_check_bgnend(char *data);
char	*ft_strdup_map(const char *s1, int len);
int		ft_check_openmap(char **data);
char    **ft_split_map(t_struct *cub);
char    *ft_search_inmap(t_struct *cub, char *search, int len_ofsrch);
void    ft_draw_map(t_struct *cub);
void 	player_position(t_struct *cub);
int		player_move(t_struct *cub);
void 	directionOfPlayer(t_struct *cub);
void 	ddaForLine(t_struct *cub,int x_0, int y_0, int x_1, int y_1, int color);
int 	check_wall(t_struct *cub, double x, double y);
void 	drawRaysOfplyer(t_struct *cub, int x, int y, int color);
int		castRays(t_struct *cub);
void 	check_nextSteep(t_struct *cub);
void	check_downSteep(t_struct *cub);
double	normalizeAngle(double angle);
double 	calculDistance(double wallHit_X, double wallHit_y, double x, double y);
void 	castHrzntalRays(t_struct *cub);
void 	castVrtcalRays(t_struct *cub);
void 	castAllRays(t_struct *cub);
void 	drawRaysOfplyer_mini(t_struct *cub, int x, int y, int color);
int 	ft_count_height(t_struct *cub);
void	my_mlx_pixel_put(t_struct *ptr, int x, int y, unsigned int color);
void    ft_jump_lines(t_struct *cub);
void 	ft_colorBuffer(t_struct *cub);
double	degrees_to_radians(double a);
int		is_ceiling(unsigned int **buffer, int i, int k);
int		is_floor(unsigned int **buffer, int i, int k);
int		KeyRelease(int key, t_struct *cub);
int		KeyPress(int key, t_struct *cub);
int 	handling_rgb(char *data);
int		ft_check_isnum(char *num);
int 	typeofFile(char *path, char *type, int len);
void	loading_map(t_struct *cub);
int 	MotionNotify(int x, int y, t_struct *cub);
int		ft_close(int keycode);
void print(char **str);
#endif