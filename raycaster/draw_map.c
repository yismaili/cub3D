/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:33 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/29 15:03:42 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	my_mlx_pixel_put(t_struct *ptr, int x, int y, unsigned int color)
{
	char	*dst;

	if (x > 0 && y > 0 && x < W_WIDTH && y < W_HEIGHT)
	{
		dst = (char *)ptr->addr + (y * ptr->line_length + x
				* (ptr->bits_per_pixel / 8));
		*( unsigned int *)dst = color;
	}
}

int ft_count_height(t_struct *cub)
{
    int len;
    int i;
    int j;

    i = 0;
    len = 0;
    while (cub->my_map[i])
    {
        j = 0;
        while (cub->my_map[i][j])
        {
          if (j == 0)
            len++;
          j++;  
        }
      i++;  
    }
   return (len); 
}

void    draw_cub(t_struct *ptr, int x, int y, int color)
{
    int start_x;
    int start_y;
    int     i;
    int     j;

        
        start_x =  x * ptr->mini_map.mini_scaleWidth;
        start_y =  y * ptr->mini_map.mini_scaleHeight;
        i = start_y;
        j = start_x;
        while (i < start_y + ptr->mini_map.mini_scaleHeight)
        {
            j =  start_x;
            while (j < start_x + ptr->mini_map.mini_scaleWidth)
            {
                my_mlx_pixel_put(ptr, j, i, color);
                j++;
            }
        i++;
    }
}

void    ft_draw_map(t_struct *cub)
{
    int x;
    int y;
    int     len;

    y = 0;
    len = 0;
    int xx = (cub->player.position_x/ cub->scaleWidth) * cub->mini_map.mini_scaleWidth;
    int yy = (cub->player.position_y / cub->scaleHeight) * cub->mini_map.mini_scaleHeight;
    mlx_clear_window(cub->mlx_ptr, cub->win_ptr);
    drawRaysOfplyer(cub, cub->player.position_x, cub->player.position_y , 0xFFFF0F); 
    while (cub->my_map[y])
    {
        x = 0;
        while (cub->my_map[y][x])
        {
            if (cub->my_map[y][x] == '1')
               draw_cub(cub, x, y, 0xFFF0000);
            x++;
        }
        y++;
    }
    drawRaysOfplyer_mini(cub, xx, yy , 0xFFFF0F);     
    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
}

void player_position(t_struct *cub){
    int i = 0;
    int j = 0;
  
    cub->scaleHeight = 64;
    cub->scaleWidth = 64;
    cub->player.rottSpeed = 0.174533;
    cub->player.walkDrctn = 0;
    cub->numOfRays = W_WIDTH;
   while (cub->my_map[i])
   {
        j = 0;
        while(cub->my_map[i][j])
        {
            if (cub->my_map[i][j] == 'E'|| cub->my_map[i][j] == 'N' || cub->my_map[i][j] == 'S' || cub->my_map[i][j] == 'W')
            {
                cub->player.position_x = j * cub->scaleWidth;
                cub->player.position_y = i * cub->scaleHeight;
                cub->mini_map.mini_scaleWidth = (W_WIDTH / cub->width)/ 4;
                cub->mini_map.mini_scaleHeight = (W_HEIGHT / cub->heightof_minimap) / 4;
                return ;
            }
            j++;
        }
        i++;
   } 
}


void directionOfPlayer(t_struct *cub)
{
    int gred_y = floor(cub->player.position_y / cub->scaleHeight);
    int gred_x = floor(cub->player.position_x / cub->scaleWidth);
    if (cub->my_map[gred_y][gred_x] == 'N')
        cub->player.rottAngle = M_PI / 2;
    if (cub->my_map[gred_y][gred_x] == 'S')
        cub->player.rottAngle = M_PI * (3/ 2);
    if (cub->my_map[gred_y][gred_x] == 'W')
        cub->player.rottAngle = M_PI;
    if (cub->my_map[gred_y][gred_x] == 'E')
        cub->player.rottAngle = 0;
}

void	color_oftexture(t_struct *cub)
{
	int			i;
	int			j;
	
	i = -1;
	while (++i < W_HEIGHT)
		cub->color_buffer[i] = (unsigned int *)ft_calloc(sizeof(unsigned int), \
				W_WIDTH);
	ft_colorBuffer(cub);
	cub->wallTexture = (unsigned int *) ft_calloc (sizeof(unsigned int), \
			(unsigned int)cub->scaleWidth * (unsigned int)cub->scaleHeight);
	i = 0;
	while (i < cub->scaleWidth)
	{
		j = 0;
		while (j < cub->scaleHeight)
		{
			if (i % 8 && j % 8)
				cub->wallTexture[(cub->scaleWidth * j) + i] = 0xadd8e6;
			else
				cub->wallTexture[(cub->scaleWidth * j) + i] = 0xFFF0000;
			j++;
		}
		i++;
	}
}
void	init_textures(t_struct *cub)
{
	cub->texture = malloc(sizeof(t_textures) * 4);
	load_texture(cub, cub->texture);
}

void	load_texture(t_struct *c, t_textures *t)
{
	t[0].img = mlx_xpm_file_to_image(c->mlx_ptr, c->drct.north_path, \
			&t[0].img_width, &t[0].img_height);
	t[0].data = (int *)mlx_get_data_addr(t[0].img, \
			&t[0].bits_per_pixel, &t[0].size_line, \
			&t[0].endian);
	t[1].img = mlx_xpm_file_to_image(c->mlx_ptr, c->drct.south_path, \
			&t[1].img_width, &t[1].img_height);
	t[1].data = (int *)mlx_get_data_addr(t[1].img, \
			&t[1].bits_per_pixel, &t[1].size_line, \
			&t[1].endian);
	t[2].img = mlx_xpm_file_to_image(c->mlx_ptr, c->drct.east_path, \
			&t[2].img_width, &t[2].img_height);
	t[2].data = (int *)mlx_get_data_addr(t[2].img, \
			&t[2].bits_per_pixel, &t[2].size_line, \
			&t[2].endian);
	t[3].img = mlx_xpm_file_to_image(c->mlx_ptr, c->drct.west_path, \
			&t[3].img_width, &t[3].img_height);
	t[3].data = (int *)mlx_get_data_addr(t[3].img, \
			&t[3].bits_per_pixel, \
			&t[3].size_line, &t[3].endian);
	if (!t[0].img || !t[1].img || !t[2].img || \
			!t[3].img)
		return ;
	if (!t[0].data || !t[1].data || !t[2].data || \
			!t[3].data)
		return ;
	if (t[0].img_width != t[0].img_height || t[1]. \
			img_width != t[1].img_height || t[2]. \
			img_width != t[2].img_height || t[3]. \
			img_width != t[3].img_height)
		return ;
}
