/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:48:33 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/30 19:36:57 by yismaili         ###   ########.fr       */
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
		*(unsigned int *)dst = color;
	}
}

void	draw_cub(t_struct *ptr, int x, int y, int color)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = x * ptr->mini_map.mini_scalewidth;
	start_y = y * ptr->mini_map.mini_scaleheight;
	i = start_y;
	j = start_x;
	while (i < start_y + ptr->mini_map.mini_scaleheight)
	{
		j = start_x;
		while (j < start_x + ptr->mini_map.mini_scalewidth)
		{
			my_mlx_pixel_put(ptr, j, i, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_map(t_struct *cub)
{
	cub->tmp.y = 0;
	cub->tmp.xx = (cub->player.position_x / cub->scalewidth) * cub->mini_map. \
		mini_scalewidth;
	cub->tmp.yy = (cub->player.position_y / cub->scaleheight) * cub->mini_map. \
		mini_scaleheight;
	mlx_clear_window(cub->mlx_ptr, cub->win_ptr);
	randering_wall(cub);
	while (cub->my_map[cub->tmp.y])
	{
		cub->tmp.x = 0;
		while (cub->my_map[cub->tmp.y][cub->tmp.x])
		{
			if (cub->my_map[cub->tmp.y][cub->tmp.x] == '1')
				draw_cub(cub, cub->tmp.x, cub->tmp.y, 0xFFF0000);
			cub->tmp.x++;
		}
		cub->tmp.y++;
	}
	drawrays_of_plyer_mini(cub, cub->tmp.xx, cub->tmp.yy);
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
}

void	player_position(t_struct *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub->my_map[i])
	{
		j = 0;
		while (cub->my_map[i][j])
		{
			if (cub->my_map[i][j] == 'E' || cub->my_map[i][j] == 'N' || \
					cub->my_map[i][j] == 'S' || cub->my_map[i][j] == 'W')
			{
				cub->player.position_x = j * cub->scalewidth;
				cub->player.position_y = i * cub->scaleheight;
				cub->mini_map.mini_scalewidth = (W_WIDTH / cub->width) / 4;
				cub->mini_map.mini_scaleheight = \
										(W_HEIGHT / cub->heightof_minimap) / 4;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	direction_of_player(t_struct *cub)
{
	int	gred_y;
	int	gred_x;

	gred_y = floor(cub->player.position_y / cub->scaleheight);
	gred_x = floor(cub->player.position_x / cub->scalewidth);
	if (cub->my_map[gred_y][gred_x] == 'N')
		cub->player.rottangle = (M_PI * 3) / 2;
	if (cub->my_map[gred_y][gred_x] == 'S')
		cub->player.rottangle = M_PI / 2;
	if (cub->my_map[gred_y][gred_x] == 'W')
		cub->player.rottangle = M_PI;
	if (cub->my_map[gred_y][gred_x] == 'E')
		cub->player.rottangle = 0;
}
