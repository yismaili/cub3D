/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:56:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/11 13:56:53 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# define W_WIDTH 1020
# define W_HEIGHT 510

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
	int 	position_x;
	int 	position_y;
	int plyrPostin_x;
	int plyrPostin_y;
	float 	rottAngle;
}  t_player;

typedef struct s_struct
{
	char		**map;
	t_ceilling 	clg;
	t_floor		flr;
	t_dirct		drct;
	int			height;
	int			width;
	int			len_ofmap;
	void		*mlx_ptr;
    void		*win_ptr;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int 		checkColorMap;
	int 		scaleHeight;
	int 		scaleWidth;
	t_player 	player;
}	t_struct;


int     get_height(char *map_file);
int		get_width(char *map_file, int height);
char    *ft_check_map(t_struct *cub);
char	*get_next_line(int fd);
void	ft_read_maps(char *map_file, t_struct *ptr);
char    *ft_check_texture(t_struct *cub, char *dirct, int len);
char    *ft_search_innewmap(char **new_map, char *search, int len_ofsrch);
int		ft_check_alltextures(t_struct *cub);
char    **ft_check_florclg(t_struct *cub, char *flor_clg, int len);
int		ft_check_rgb(t_struct *cub);
int		ft_check_double(t_struct *cub, char *dirct, int len);
int		ft_check_alldouble(t_struct *cub);
char    **ft_jump_lines(t_struct *cub);
int 	ft_check_bgnend(char *data);
char	*ft_strdup_map(const char *s1, int len);
int		ft_check_openmap(char **data);
char    **ft_split_map(t_struct *cub);
char    *ft_search_inmap(t_struct *cub, char *search, int len_ofsrch);
void    ft_draw_map(t_struct *cub);
void 	player_position(t_struct *cub);
int		player_move(int key, t_struct *p);
void 	directionOfPlayer(t_struct *cub);
void 	draw_player(t_struct *cub, int x, int y, int color);
void 	ddaForLine(t_struct *cub,int x_0, int y_0, int x_1, int y_1, int color);
 int 	check_wall(t_struct *cub);
void print(char **str);
#endif