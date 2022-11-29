/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:26:18 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/29 16:49:55 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	color_oftexture(t_struct *cub)
{
	int	i;
	int	j;

	i = -1;
	while (++i < W_HEIGHT)
		cub->color_buffer[i] = (unsigned int *)ft_calloc(sizeof(unsigned int), \
				W_WIDTH);
	ft_color_buffer(cub);
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
	t[0].data = (int *)mlx_get_data_addr(t[0].img, &t[0].bits_per_pixel, \
			&t[0].size_line, &t[0].endian);
	t[1].img = mlx_xpm_file_to_image(c->mlx_ptr, c->drct.south_path, \
			&t[1].img_width, &t[1].img_height);
	t[1].data = (int *)mlx_get_data_addr(t[1].img, &t[1].bits_per_pixel, \
			&t[1].size_line, &t[1].endian);
	t[2].img = mlx_xpm_file_to_image(c->mlx_ptr, c->drct.east_path, \
			&t[2].img_width, &t[2].img_height);
	t[2].data = (int *)mlx_get_data_addr(t[2].img, &t[2].bits_per_pixel, \
			&t[2].size_line, &t[2].endian);
	t[3].img = mlx_xpm_file_to_image(c->mlx_ptr, c->drct.west_path, \
			&t[3].img_width, &t[3].img_height);
	t[3].data = (int *)mlx_get_data_addr(t[3].img, &t[3].bits_per_pixel, \
			&t[3].size_line, &t[3].endian);
	if (!t[0].img || !t[1].img || !t[2].img || !t[3].img)
		return ;
	if (!t[0].data || !t[1].data || !t[2].data || !t[3].data)
		return ;
	if (t[0].img_width != t[0].img_height || t[1].img_width != t[1].img_height \
			|| t[2].img_width != t[2].img_height || t[3].img_width != t[3]. \
			img_height)
		return ;
}

int	ft_count_height(t_struct *cub)
{
	int	len;
	int	i;
	int	j;

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
